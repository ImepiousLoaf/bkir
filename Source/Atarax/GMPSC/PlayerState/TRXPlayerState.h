// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "TRXPlayerState.generated.h"

class UTRXEnergyAttributeSet;
class UTRXHealthAttributeSet;
class UTRXAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class ATARAX_API ATRXPlayerState : public APlayerState, public IAbilitySystemInterface
{
public:
	const TObjectPtr<UTRXHealthAttributeSet>& GetHealthAttributeSet() const;
	const TObjectPtr<UTRXEnergyAttributeSet>& GetEnergyAttributeSet() const;

private:
	GENERATED_BODY()

public:
	ATRXPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
private:
	UPROPERTY()
	TObjectPtr<UTRXAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UTRXHealthAttributeSet> HealthAttributeSet;
	UPROPERTY()
	TObjectPtr<UTRXEnergyAttributeSet> EnergyAttributeSet;
	
};
