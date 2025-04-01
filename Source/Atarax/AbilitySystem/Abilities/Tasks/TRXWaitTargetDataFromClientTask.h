// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "TRXWaitTargetDataFromClientTask.generated.h"

/**
 * 
 */
UCLASS()
class ATARAX_API UTRXWaitTargetDataFromClientTask : public UAbilityTask
{
	GENERATED_UCLASS_BODY()
	
	UPROPERTY(BlueprintAssignable)
	FWaitTargetDataDelegate ValidData;
	
	UFUNCTION(BlueprintCallable, meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true", HideSpawnParms = "Instigator"), Category = "Ability|Tasks")
	static UTRXWaitTargetDataFromClientTask* WaitTargetDataFromClient(UGameplayAbility* OwningAbility, FName TaskInstanceName, bool TriggerOnce);

	virtual void Activate() override;

	UFUNCTION()
	void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& Data, FGameplayTag ActivationTag);

protected:
	virtual void OnDestroy(bool AbilityEnded) override;

	bool bTriggerOnce;
};