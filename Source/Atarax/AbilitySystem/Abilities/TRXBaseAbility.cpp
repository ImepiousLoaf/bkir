// Fill out your copyright notice in the Description page of Project Settings.


#include "TRXBaseAbility.h"

#include "AbilitySystemComponent.h"

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
