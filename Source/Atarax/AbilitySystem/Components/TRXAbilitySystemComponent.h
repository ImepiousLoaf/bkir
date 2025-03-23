// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "TRXAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ATARAX_API UTRXAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()


	virtual void AbilityLocalInputPressed(int32 InputID) override;
	virtual void AbilityLocalInputReleased(int32 InputID) override;
};
