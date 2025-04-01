// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TRXCharacterMovementComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ATARAX_API UTRXCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

	class FTRXSavedMove_Character : public FSavedMove_Character
	{
		virtual void PrepMoveFor(ACharacter* C) override;
		virtual void SetMoveFor(ACharacter* C, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData) override;
		virtual void Clear() override;
		virtual uint8 GetCompressedFlags() const override;
		virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const override;

		bool Saved_IsWandSprint : 1;
	};

	class FTRXNetworkPreditionData : public FNetworkPredictionData_Client_Character
	{
		typedef FNetworkPredictionData_Client_Character Super;
	public:
		FTRXNetworkPreditionData(const UCharacterMovementComponent& InMovementComponent);
		virtual FSavedMovePtr AllocateNewMove() override;
	};
	
public:
	// Sets default values for this component's properties
	UTRXCharacterMovementComponent();
	

	UFUNCTION(BlueprintCallable)
	void SetIsWantSprint(const bool IsWantSprint);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;
	virtual void UpdateFromCompressedFlags(uint8 Flags) override;
	virtual void OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity) override;
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	bool Safe_IsWandSprint : 1;
	void SetIsWantSprintInternal_(bool IsWantSprint);
	UFUNCTION(Server, Reliable)
	void Server_SetIsWantSprint(bool IsWantSprint);
};
