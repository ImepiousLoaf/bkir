// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TRXBaseAttributeSet.h"
#include "TRXEnergyAttributeSet.generated.h"

struct FGameplayAttributeData;
/**
 * 
 */
UCLASS()
class ATARAX_API UTRXEnergyAttributeSet : public UTRXBaseAttributeSet
{
	GENERATED_BODY()
public:
	UTRXEnergyAttributeSet();
protected:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
private:
	UFUNCTION()
	void OnRep_Energy(const FGameplayAttributeData& OldEnergy) const;
	
	UFUNCTION()
	void OnRep_MaxEnergy(const FGameplayAttributeData& OldMaxEnergy) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Energy, meta =(AllowPrivateAccess = true))
	FGameplayAttributeData Energy;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_MaxEnergy, meta =(AllowPrivateAccess = true))
	FGameplayAttributeData MaxEnergy;
	
	ATTRIBUTE_ACCESSORS(ThisClass, Energy)
	ATTRIBUTE_ACCESSORS(ThisClass, MaxEnergy)
};
