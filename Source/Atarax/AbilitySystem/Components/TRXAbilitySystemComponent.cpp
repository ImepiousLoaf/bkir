// Fill out your copyright notice in the Description page of Project Settings.


#include "TRXAbilitySystemComponent.h"

#include "Atarax/AbilitySystem/Abilities/TRXBaseAbility.h"

#pragma optimize("", off)
UTRXBaseAbility* UTRXAbilitySystemComponent::GetPrimaryAbilityInstanceFromClass(TSubclassOf<UGameplayAbility> AbilityClass, UObject* OptionalSourceObject)
{
	const FGameplayAbilitySpecHandle Handle = FindAblitySpecHandleFromClass(AbilityClass, OptionalSourceObject);
	if (const FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(Handle))
	{
		return Cast<UTRXBaseAbility>(AbilitySpec->GetPrimaryInstance());
	}

	return nullptr;
}

FGameplayAbilitySpecHandle UTRXAbilitySystemComponent::FindAblitySpecHandleFromClass(TSubclassOf<UGameplayAbility> AbilityClass, UObject* OptionalSourceObject)
{
	ABILITYLIST_SCOPE_LOCK();
	for (FGameplayAbilitySpec& Spec : ActivatableAbilities.Items)
	{
		TSubclassOf<UGameplayAbility> SpecAbilityClass = Spec.Ability->GetClass();
		if (SpecAbilityClass == AbilityClass)
		{
			if (!OptionalSourceObject || (OptionalSourceObject && Spec.SourceObject == OptionalSourceObject))
			{
				return Spec.Handle;
			}
		}
	}

	return FGameplayAbilitySpecHandle();
}

bool UTRXAbilitySystemComponent::FindAblitySpecFromClass(TSubclassOf<UGameplayAbility> AbilityClass, UObject* OptionalSourceObject, FGameplayAbilitySpec& SpecOut)
{
	ABILITYLIST_SCOPE_LOCK();
	for (FGameplayAbilitySpec& Spec : ActivatableAbilities.Items)
	{
		TSubclassOf<UGameplayAbility> SpecAbilityClass = Spec.Ability->GetClass();
		if (SpecAbilityClass == AbilityClass)
		{
			if (!OptionalSourceObject || (OptionalSourceObject && Spec.SourceObject == OptionalSourceObject))
			{
				SpecOut = Spec;
				return true;
			}
		}
	}
	SpecOut = nullptr;
	return false;
}

void UTRXAbilitySystemComponent::AbilityLocalInputPressed(int32 InputID)
{
	//Super::AbilityLocalInputPressed(InputID);
	ABILITYLIST_SCOPE_LOCK()
	for (auto& Spec : ActivatableAbilities.Items)
	{
		if(!Spec.Ability)
			continue;

		if(static_cast<int>(Cast<UTRXBaseAbility>(Spec.Ability)->InputId) == InputID)
		{
			Spec.InputPressed = true;
			if(Spec.IsActive())
			{
				if(Spec.Ability->bReplicateInputDirectly && !IsOwnerActorAuthoritative())
				{
					ServerSetInputPressed(Spec.Handle);
				}

				AbilitySpecInputPressed(Spec);

				InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec.Handle, Spec.ActivationInfo.GetActivationPredictionKey());
			}
			else
			{
				UTRXBaseAbility* GA = Cast<UTRXBaseAbility>(Spec.Ability);
				if(GA && GA->ActivateOnInput)
				{
					TryActivateAbility(Spec.Handle);
				}
			}
		}	
	}
}

void UTRXAbilitySystemComponent::AbilityLocalInputReleased(int32 InputID)
{
	//Super::AbilityLocalInputReleased(InputID);
	ABILITYLIST_SCOPE_LOCK()
	for (auto& Spec : ActivatableAbilities.Items)
	{
		if(!Spec.Ability)
			continue;

		if(static_cast<int>(Cast<UTRXBaseAbility>(Spec.Ability)->InputId) == InputID)
		{
			Spec.InputPressed = false;
			if(Spec.IsActive())
			{
				if(Spec.Ability->bReplicateInputDirectly && !IsOwnerActorAuthoritative())
				{
					ServerSetInputReleased(Spec.Handle);
				}
				AbilitySpecInputReleased(Spec);
				//AbilitySpecInputPressed(Spec);
				
				InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, Spec.Handle, Spec.ActivationInfo.GetActivationPredictionKey());
			}
		}	
	}
}