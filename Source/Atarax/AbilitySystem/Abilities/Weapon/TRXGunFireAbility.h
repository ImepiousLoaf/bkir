// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Atarax/AbilitySystem/Abilities/TRXBaseAbility.h"
#include "TRXGunFireAbility.generated.h"

/**
 * 
 */
UCLASS()
class ATARAX_API UTRXGunFireAbility : public UTRXBaseAbility
{
	GENERATED_BODY()
public:
	UTRXGunFireAbility();

protected:
	//~UXCLGameplayAbility interface
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void ActivateLocalPlayerAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);
	//~End of UXCLGameplayAbility interface

	//~UXCLGameplayAbility_ClientToServer interface
	virtual void ActivateAbilityWithTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle, FGameplayTag ApplicationTag);
	//~End of UXCLGameplayAbility_ClientToServer interface
	virtual void NotifyTargetDataReady(const FGameplayAbilityTargetDataHandle& InData, FGameplayTag ApplicationTag);

	
	virtual void ActivateServerAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);

	virtual void EndAbilityCleanup(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

private:
	FDelegateHandle NotifyTargetDataReadyDelegateHandle;
};
