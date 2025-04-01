// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "TRXAbilitySystemComponent.generated.h"

/**
 * 
 */


class UTRXBaseAbility;

UCLASS(Blueprintable)
class ATARAX_API UTRXAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ability")
	UTRXBaseAbility* GetPrimaryAbilityInstanceFromClass(TSubclassOf<UGameplayAbility> AbilityClass, UObject* OptionalSourceObject);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ability")
	FGameplayAbilitySpecHandle FindAblitySpecHandleFromClass(TSubclassOf<UGameplayAbility> AbilityClass, UObject* OptionalSourceObject);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ability")
	bool FindAblitySpecFromClass(TSubclassOf<UGameplayAbility> AbilityClass, UObject* OptionalSourceObject, FGameplayAbilitySpec& SpecOut);
	virtual void AbilityLocalInputPressed(int32 InputID) override;
	virtual void AbilityLocalInputReleased(int32 InputID) override;
};
