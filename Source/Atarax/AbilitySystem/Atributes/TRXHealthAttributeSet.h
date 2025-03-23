// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TRXBaseAttributeSet.h"
#include "TRXHealthAttributeSet.generated.h"

struct FGameplayAttributeData;
/**
 * 
 */
UCLASS()
class ATARAX_API UTRXHealthAttributeSet : public UTRXBaseAttributeSet
{
	GENERATED_BODY()
public:
	UTRXHealthAttributeSet();
protected:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
private:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Health, meta =(AllowPrivateAccess = true))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_MaxHealth, meta =(AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;
	
	ATTRIBUTE_ACCESSORS(ThisClass, Health)
	ATTRIBUTE_ACCESSORS(ThisClass, MaxHealth)
};
