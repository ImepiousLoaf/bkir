// Fill out your copyright notice in the Description page of Project Settings.


#include "TRXPlayerState.h"

#include "Atarax/AbilitySystem/Atributes/TRXEnergyAttributeSet.h"
#include "Atarax/AbilitySystem/Atributes/TRXHealthAttributeSet.h"
#include "Atarax/AbilitySystem/Components/TRXAbilitySystemComponent.h"

const TObjectPtr<UTRXHealthAttributeSet>& ATRXPlayerState::GetHealthAttributeSet() const
{
	return HealthAttributeSet;
}

const TObjectPtr<UTRXEnergyAttributeSet>& ATRXPlayerState::GetEnergyAttributeSet() const
{
	return EnergyAttributeSet;
}

ATRXPlayerState::ATRXPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UTRXAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	NetUpdateFrequency = 100.0f;

	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);
	AbilitySystemComponent->SetIsReplicated(true);
	//AbilitySystemComponent->bReplicateInstancedAbilities = true;
	HealthAttributeSet = CreateDefaultSubobject<UTRXHealthAttributeSet>(TEXT("Attribute Health"));
	EnergyAttributeSet = CreateDefaultSubobject<UTRXEnergyAttributeSet>(TEXT("Attribute Energy"));
}

UAbilitySystemComponent* ATRXPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
