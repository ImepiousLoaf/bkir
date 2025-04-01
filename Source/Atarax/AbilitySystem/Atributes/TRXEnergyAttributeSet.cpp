// Fill out your copyright notice in the Description page of Project Settings.


#include "TRXEnergyAttributeSet.h"


#include "Net/UnrealNetwork.h"

void UTRXEnergyAttributeSet::OnRep_Energy(const FGameplayAttributeData& OldEnergy) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Energy, OldEnergy);
}

void UTRXEnergyAttributeSet::OnRep_MaxEnergy(const FGameplayAttributeData& OldMaxEnergy) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxEnergy, OldMaxEnergy);
}

UTRXEnergyAttributeSet::UTRXEnergyAttributeSet()
{
	InitEnergy(100);
	InitMaxEnergy(100);
}

void UTRXEnergyAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Energy, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxEnergy, COND_None, REPNOTIFY_Always);
}

void UTRXEnergyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if(Attribute == GetEnergyAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, MaxEnergy.GetCurrentValue());
	}
}
