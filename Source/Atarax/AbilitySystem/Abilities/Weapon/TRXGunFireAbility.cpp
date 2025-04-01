// Fill out your copyright notice in the Description page of Project Settings.


#include "TRXGunFireAbility.h"

#include "AbilitySystemComponent.h"

UTRXGunFireAbility::UTRXGunFireAbility()
{
}

void UTRXGunFireAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	ActivateServerAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UTRXGunFireAbility::ActivateLocalPlayerAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	// Compute the TargetData
	FVector ClientLocation = FVector::ZeroVector;  // some value you compute

	// Format the TargetData for GAS RPC

	FGameplayAbilityTargetDataHandle TargetDataHandle;
	FGameplayAbilityTargetData_LocationInfo* TargetData = new FGameplayAbilityTargetData_LocationInfo(); //** USE OF new() IS **REQUIRED** **

	TargetData->TargetLocation.LocationType = EGameplayAbilityTargetingLocationType::LiteralTransform;
	TargetData->TargetLocation.LiteralTransform = FTransform(ClientLocation);

	TargetDataHandle.Add(TargetData);

	// Notify self (local client) *AND* server that TargetData is ready to be processed
	NotifyTargetDataReady(TargetDataHandle, FGameplayTag());  // send with a gameplay tag, or empty
}

void UTRXGunFireAbility::ActivateAbilityWithTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle, FGameplayTag ApplicationTag)
{
	// retrieve data
	const FGameplayAbilityTargetData* TargetData = TargetDataHandle.Get(0);
	if (!TargetData)
	{
		// client sent us bad data
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
		return;
	}

	// decode data
	const FVector ClientLocation = TargetData->GetEndPoint();

	// Server: Validate data
	const bool bIsServer = CurrentActorInfo->IsNetAuthority();
	if (bIsServer)
	{
		if (ClientLocation.X < 0)  // if negative X is prohibited by server for some reason
		{
			CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
			return;
		}
	}

	//////////////////////////////////////////////////////////////////////
	// Client & Server both -- data is valid, activate the ability with it
	//////////////////////////////////////////////////////////////////////

	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Magenta, "Sobaka");
	
	// in this case we just log a message:
	//XCL_GALOG(TEXT("ClientLocation = %s"), *ClientLocation.ToString());

	// this is an instant ability, end it immediately (only replicate if bIsServer)
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bIsServer, false);
}

void UTRXGunFireAbility::NotifyTargetDataReady(const FGameplayAbilityTargetDataHandle& InData, FGameplayTag ApplicationTag)
{
	UAbilitySystemComponent* ASC = CurrentActorInfo->AbilitySystemComponent.Get();
	check(ASC);

	// [xist] is this (from Lyra) like an "if is handle valid?" check? seems so, keeping it as such.
	if (!ASC->FindAbilitySpecFromHandle(CurrentSpecHandle))
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);  // do not replicate
		return;
	}

	// if commit fails, cancel ability
	if (!CommitAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo))
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);  // replicate cancellation
		return;
	}

	// true if we need to replicate this target data to the server
	const bool bShouldNotifyServer = CurrentActorInfo->IsLocallyControlled() && !CurrentActorInfo->IsNetAuthority();

	// Start a scoped prediction window
	FScopedPredictionWindow	ScopedPrediction(ASC);

	// Lyra does this memcopy operation; const cast paranoia is real. We'll keep it.
	// Take ownership of the target data to make sure no callbacks into game code invalidate it out from under us
	const FGameplayAbilityTargetDataHandle LocalTargetDataHandle(MoveTemp(const_cast<FGameplayAbilityTargetDataHandle&>(InData)));

	// if this isn't the local player on the server, then notify the server
	if (bShouldNotifyServer)
		ASC->CallServerSetReplicatedTargetData(CurrentSpecHandle, CurrentActivationInfo.GetActivationPredictionKey(), LocalTargetDataHandle, ApplicationTag, ASC->ScopedPredictionKey);

	// Execute the ability we've now successfully committed
	ActivateAbilityWithTargetData(LocalTargetDataHandle, ApplicationTag);

	// We've processed the data, clear it from the RPC buffer
	ASC->ConsumeClientReplicatedTargetData(CurrentSpecHandle, CurrentActivationInfo.GetActivationPredictionKey());
}

void UTRXGunFireAbility::ActivateServerAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
	check(ASC);

	// plug into AbilitySystemComponent to receive Target Data from client
	NotifyTargetDataReadyDelegateHandle = ASC->AbilityTargetDataSetDelegate(Handle, ActivationInfo.GetActivationPredictionKey()).AddUObject(this, &ThisClass::NotifyTargetDataReady);
}

void UTRXGunFireAbility::EndAbilityCleanup(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	UAbilitySystemComponent* ASC = CurrentActorInfo->AbilitySystemComponent.Get();
	check(ASC);

	// clean up the mess we made in ASC
	ASC->AbilityTargetDataSetDelegate(CurrentSpecHandle, CurrentActivationInfo.GetActivationPredictionKey()).Remove(NotifyTargetDataReadyDelegateHandle);
	ASC->ConsumeClientReplicatedTargetData(CurrentSpecHandle, CurrentActivationInfo.GetActivationPredictionKey());
}

void UTRXGunFireAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	EndAbilityCleanup(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UTRXGunFireAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);
	const FGameplayAbilityActivationInfo ActivationInfo = GetCurrentActivationInfo();
	if(HasAuthority(&ActivationInfo))
	{
		ActivateServerAbility(Spec.Handle, ActorInfo, ActivationInfo, &CurrentEventData);
	}
}
