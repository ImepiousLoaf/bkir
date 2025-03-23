// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "TRXBaseAbility.generated.h"

/**
 * 
 */


UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
	None,
	Interact,
	Ability1,
	Ability2,
	Ability3
};

UCLASS()
class ATARAX_API UTRXBaseAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAbilityInputID InputId = EAbilityInputID::None;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool ActivateOnGranted = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool ActivateOnInput = true;
	UTRXBaseAbility();

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	UFUNCTION(BlueprintCallable)
	EAbilityInputID GetInputID() const;
};




