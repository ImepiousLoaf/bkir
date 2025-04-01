// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "TRXBaseAbility.generated.h"

/**
 * 
 */


struct FTRXTargetData;

UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
	None,
	Confirm,
	Cancel,
	Ability1,
	Ability2,
	Ability3,
	Ability4,
};

UCLASS()
class ATARAX_API UTRXBaseAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	FGameplayAbilityTargetDataHandle MakeTargetDataFromTRXTargetData(FTRXTargetData in);
	UFUNCTION(BlueprintCallable)
	const FTRXTargetData GetTargetDataFromTRXTargetData(const FGameplayAbilityTargetDataHandle& TargetData, int32 Index);
	UFUNCTION(BlueprintCallable)
	void SendTargetData(const FGameplayAbilityTargetDataHandle Data);
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




