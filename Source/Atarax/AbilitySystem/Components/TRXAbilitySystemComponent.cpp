// Fill out your copyright notice in the Description page of Project Settings.


#include "TRXAbilitySystemComponent.h"

#include "Atarax/AbilitySystem/Abilities/TRXBaseAbility.h"


void UTRXAbilitySystemComponent::AbilityLocalInputPressed(int32 InputID)
{
	//Super::AbilityLocalInputPressed(InputID);
	ABILITYLIST_SCOPE_LOCK()
	for (auto& Spec : ActivatableAbilities.Items)
	{
		if(!Spec.Ability)
			continue;

		if(Spec.InputID == InputID)
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

		if(Spec.InputID == InputID)
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