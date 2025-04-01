// Fill out your copyright notice in the Description page of Project Settings.


#include "TRXBaseAbility.h"

#include "AbilitySystemComponent.h"
#include "TargetData/TRXTargetData.h"

FGameplayAbilityTargetDataHandle UTRXBaseAbility::MakeTargetDataFromTRXTargetData(FTRXTargetData in)
{
	auto rer = new FTRXTargetData(in);
	// Give it a handle and return
	FGameplayAbilityTargetDataHandle	Handle;
	Handle.Data.Add(TSharedPtr<FTRXTargetData>(rer));
	return Handle;
}

const FTRXTargetData UTRXBaseAbility::GetTargetDataFromTRXTargetData(const FGameplayAbilityTargetDataHandle& TargetData, int32 Index)
{
	if (TargetData.Data.IsValidIndex(Index))
	{
		if (FGameplayAbilityTargetData* Data = TargetData.Data[Index].Get())
		{
			if (const FTRXTargetData* trx = reinterpret_cast<const FTRXTargetData*>(Data))
			{
				return *trx;
			}
		}
	}

	return FTRXTargetData();
}

void UTRXBaseAbility::SendTargetData(const FGameplayAbilityTargetDataHandle Data)
{
	UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	check(AbilitySystemComponent);
	FScopedPredictionWindow	ScopedPrediction(AbilitySystemComponent,
		true && (true && !AbilitySystemComponent->ScopedPredictionKey.IsValidForMorePrediction()));

	const FGameplayAbilityActorInfo* Info = GetCurrentActorInfo();
	if (IsPredictingClient())
	{
		
		FGameplayTag ApplicationTag; // Fixme: where would this be useful?
		AbilitySystemComponent->CallServerSetReplicatedTargetData(GetCurrentAbilitySpecHandle(), GetCurrentActivationInfo().GetActivationPredictionKey(), Data, ApplicationTag, AbilitySystemComponent->ScopedPredictionKey);
	}
	//
	// if (ShouldBroadcastAbilityTaskDelegates())
	// {
	// 	ValidData.Broadcast(Data);
	// }
	//
	// if (ConfirmationType != EGameplayTargetingConfirmation::CustomMulti)
	// {
	// 	EndTask();
	// }
}

UTRXBaseAbility::UTRXBaseAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UTRXBaseAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);
	if(ActivateOnGranted)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}

EAbilityInputID UTRXBaseAbility::GetInputID() const
{
	return InputId;
}
