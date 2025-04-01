// Fill out your copyright notice in the Description page of Project Settings.


#include "TRXCharacterMovementComponent.h"

#include "GameFramework/Character.h"


void UTRXCharacterMovementComponent::FTRXSavedMove_Character::PrepMoveFor(ACharacter* C)
{
	FSavedMove_Character::PrepMoveFor(C);
	
	auto MovementComponent = C->GetCharacterMovement<UTRXCharacterMovementComponent>();
	MovementComponent->Safe_IsWandSprint = Saved_IsWandSprint;
}

void UTRXCharacterMovementComponent::FTRXSavedMove_Character::SetMoveFor(ACharacter* C, float InDeltaTime,
	FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData)
{
	FSavedMove_Character::SetMoveFor(C, InDeltaTime, NewAccel, ClientData);

	auto MovementComponent = C->GetCharacterMovement<UTRXCharacterMovementComponent>();
	Saved_IsWandSprint = MovementComponent->Safe_IsWandSprint;
}

void UTRXCharacterMovementComponent::FTRXSavedMove_Character::Clear()
{
	FSavedMove_Character::Clear();
	Saved_IsWandSprint = false;
}

uint8 UTRXCharacterMovementComponent::FTRXSavedMove_Character::GetCompressedFlags() const
{
	uint8 Flags = FSavedMove_Character::GetCompressedFlags();
	if(Saved_IsWandSprint)
	{
		Flags |= FLAG_Custom_0;
	}
	return Flags;
	
}

bool UTRXCharacterMovementComponent::FTRXSavedMove_Character::CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const
{
	const FTRXSavedMove_Character* SavedMove = static_cast<FTRXSavedMove_Character*>(NewMove.Get());
	return FSavedMove_Character::CanCombineWith(NewMove, InCharacter, MaxDelta) && Saved_IsWandSprint == SavedMove->Saved_IsWandSprint;
}

UTRXCharacterMovementComponent::FTRXNetworkPreditionData::FTRXNetworkPreditionData(const UCharacterMovementComponent& InMovementComponent) : Super(InMovementComponent)
{
	
}

FSavedMovePtr UTRXCharacterMovementComponent::FTRXNetworkPreditionData::AllocateNewMove()
{
	return MakeShared<FTRXSavedMove_Character>();
}

// Sets default values for this component's properties
UTRXCharacterMovementComponent::UTRXCharacterMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTRXCharacterMovementComponent::SetIsWantSprintInternal_(const bool IsWantSprint)
{
	Safe_IsWandSprint = IsWantSprint;
}

void UTRXCharacterMovementComponent::Server_SetIsWantSprint_Implementation(bool IsWantSprint)
{
	SetIsWantSprintInternal_(IsWantSprint);
}

void UTRXCharacterMovementComponent::SetIsWantSprint(const bool IsWantSprint)
{
	SetIsWantSprintInternal_(IsWantSprint);
}


// Called when the game starts
void UTRXCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

FNetworkPredictionData_Client* UTRXCharacterMovementComponent::GetPredictionData_Client() const
{
	if(ClientPredictionData == nullptr)
	{
		UTRXCharacterMovementComponent* MutableThis = const_cast<UTRXCharacterMovementComponent*>(this);
		MutableThis->ClientPredictionData = new FTRXNetworkPreditionData(*this);
		MutableThis->ClientPredictionData->MaxSmoothNetUpdateDist = 90.f;
		MutableThis->ClientPredictionData->NoSmoothNetUpdateDist = 200.f;
	}
	return ClientPredictionData;
}

void UTRXCharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);
	Safe_IsWandSprint = (Flags & FSavedMove_Character::FLAG_Custom_0);
}

void UTRXCharacterMovementComponent::OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation,
	const FVector& OldVelocity)
{
	Super::OnMovementUpdated(DeltaSeconds, OldLocation, OldVelocity);

	if (Safe_IsWandSprint)
	{
		MaxWalkSpeed = 1000;
	} else
	{
		MaxWalkSpeed = 600;
	}
		
}


// Called every frame
void UTRXCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

