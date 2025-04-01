// Fill out your copyright notice in the Description page of Project Settings.


#include "TRXWaitTargetDataFromClientTask.h"

#include "AbilitySystemComponent.h"

UTRXWaitTargetDataFromClientTask::UTRXWaitTargetDataFromClientTask(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UTRXWaitTargetDataFromClientTask* UTRXWaitTargetDataFromClientTask::WaitTargetDataFromClient(UGameplayAbility* OwningAbility, FName TaskInstanceName, bool TriggerOnce)
{
	UTRXWaitTargetDataFromClientTask* MyObj = NewAbilityTask<UTRXWaitTargetDataFromClientTask>(OwningAbility, TaskInstanceName);
	MyObj->bTriggerOnce = TriggerOnce;
	return MyObj;
}

void UTRXWaitTargetDataFromClientTask::Activate()
{
	Super::Activate();
	if (!Ability || !Ability->GetCurrentActorInfo()->IsNetAuthority())
	{
		return;
	}

	const FGameplayAbilitySpecHandle	SpecHandle = GetAbilitySpecHandle();
	const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
	AbilitySystemComponent->AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey).AddUObject(this, &UTRXWaitTargetDataFromClientTask::OnTargetDataReplicatedCallback);
}

void UTRXWaitTargetDataFromClientTask::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& Data, FGameplayTag ActivationTag)
{
	const FGameplayAbilityTargetDataHandle MutableData = Data;
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(MutableData);
	}

	if (bTriggerOnce)
	{
		EndTask();
	}
}

void UTRXWaitTargetDataFromClientTask::OnDestroy(bool AbilityEnded)
{
	if (AbilitySystemComponent.Get())
	{
		const FGameplayAbilitySpecHandle	SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
		AbilitySystemComponent->AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey).RemoveAll(this);
	}
	Super::OnDestroy(AbilityEnded);
}
