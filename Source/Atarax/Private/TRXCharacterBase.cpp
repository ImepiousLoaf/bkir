#include "TRXCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "Atarax/AbilitySystem/Components/TRXAbilitySystemComponent.h"
#include "Atarax/GMPSC/PlayerState/TRXPlayerState.h"

ATRXCharacterBase::ATRXCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

UAbilitySystemComponent* ATRXCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ATRXCharacterBase::InitAbilitySystem()
{
	if (ATRXPlayerState* playerState =  GetPlayerState<ATRXPlayerState>())
	{
		if (UTRXAbilitySystemComponent* abilitySystemComponent = Cast<UTRXAbilitySystemComponent>(playerState->GetAbilitySystemComponent()))
		{
			AbilitySystemComponent = abilitySystemComponent;
			AbilitySystemComponent->InitAbilityActorInfo(playerState, this);
		}
	}
}

void ATRXCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilitySystem();
}

void ATRXCharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilitySystem();
}
