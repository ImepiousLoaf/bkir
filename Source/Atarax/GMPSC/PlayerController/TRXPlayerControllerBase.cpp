#include "TRXPlayerControllerBase.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "Engine/World.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "Atarax/AbilitySystem/Abilities/TRXBaseAbility.h"
#include "Atarax/Characters/Player/TRXCharacterBase.h"
#include "Atarax/GMPSC/PlayerState/TRXPlayerState.h"
#include "Atarax/InteractionSystem/TRXInteractionComponent.h"
#include "Atarax/InteractionSystem/TRXInteractionInterface.h"
#include "Atarax/InventorySysem/TRXInventoryObject.h"
#include "Atarax/InventorySysem/Components/TRXInventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UIController/TRXUIController.h"

#pragma optimize("", off)

ATRXPlayerControllerBase::ATRXPlayerControllerBase()
{
	RotationSpeed = 10.f;
	MoveAction = nullptr;
	InputMappingContext = nullptr;
	ZoomAction = nullptr;
	bShowMouseCursor = false;
	ControlMode = FreeRotation;
	DebugTrace = false;
	PrimaryActorTick.bCanEverTick = true;

	InteractionComponent = CreateDefaultSubobject<UTRXInteractionComponent>(TEXT("InteractionComponent"));
	UIComponent = CreateDefaultSubobject<UTRXUIController>(TEXT("UIComponent"));
}

void ATRXPlayerControllerBase::Zoom_Implementation(const FInputActionValue& Value)
{
}

void ATRXPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

void ATRXPlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATRXPlayerControllerBase::Move);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ATRXPlayerControllerBase::TryInteract);
		EnhancedInputComponent->BindAction(Ability1, ETriggerEvent::Started, this,
		                                   &ATRXPlayerControllerBase::ActivateAbility1);
		EnhancedInputComponent->BindAction(Ability2, ETriggerEvent::Started, this,
		                                   &ATRXPlayerControllerBase::ActivateAbility2);
		EnhancedInputComponent->BindAction(Ability3, ETriggerEvent::Started, this,
		                                   &ATRXPlayerControllerBase::ActivateAbility3);
		EnhancedInputComponent->BindAction(Ability4, ETriggerEvent::Started, this,
		                                   &ATRXPlayerControllerBase::ActivateAbility4);
		EnhancedInputComponent->BindAction(Ability1, ETriggerEvent::Completed, this,
		                                   &ATRXPlayerControllerBase::CancelAbility1);
		EnhancedInputComponent->BindAction(Ability2, ETriggerEvent::Completed, this,
		                                   &ATRXPlayerControllerBase::CancelAbility2);
		EnhancedInputComponent->BindAction(Ability3, ETriggerEvent::Completed, this,
		                                   &ATRXPlayerControllerBase::CancelAbility3);
		EnhancedInputComponent->BindAction(Ability4, ETriggerEvent::Completed, this,
		                                   &ATRXPlayerControllerBase::CancelAbility4);
	}
}

void ATRXPlayerControllerBase::GetTargetControl(float& Yaw, float& Pitch)
{
	if (const APawn* ControlledPawn = GetPawn())
	{
		const FHitResult& HitResult = GetCursorLoc();
		const FTransform& Transform = ControlledPawn->GetTransform();
		const FVector& LastMovementInputVector = ControlledPawn->GetLastMovementInputVector();
		const UE::Math::TVector<double>& Location = Transform.GetLocation();
		const FVector FromActorToMouseDir = HitResult.Location - Location;

		if (DebugTrace)
			DrawDebugSphere(GetWorld(), HitResult.Location, 15, 12, FColor::Cyan);

		//const FVector& Velocity = Pawn->GetVelocity();
		float TargetYaw = 0;
		float TargetPitch = 0;
		if (ControlMode == FreeRotation)
		{
			;
			TargetYaw = FRotationMatrix::MakeFromX(FromActorToMouseDir).Rotator().Yaw;
			auto FowardXY = FVector(FromActorToMouseDir.X, FromActorToMouseDir.Y, 0);
			FowardXY.Normalize();
			TargetPitch = FMath::RadiansToDegrees(acosf(FVector::DotProduct(FowardXY, FromActorToMouseDir)));
			if (FromActorToMouseDir.Z < 0)
			{
				TargetPitch = -TargetPitch;
			}
		}
		else if (ControlMode == TowardControl)
		{
			TargetYaw = FRotationMatrix::MakeFromXZ(LastMovementInputVector, FVector::UpVector).Rotator().Yaw;
			TargetPitch = 0;
			//SetControlRotation(FRotator(0,Rotator.Yaw, 0));
		}
		else
		{
			checkNoEntry();
		}
		Yaw = TargetYaw;
		Pitch = TargetPitch;
		return;
	}
	Yaw = 0;
	Pitch = 0;
}

void ATRXPlayerControllerBase::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	if (IsLocalController() && GetPawn())
	{
		float TargetYaw;
		float TargetPitch;
		GetTargetControl(TargetYaw, TargetPitch);
		const FRotator TargetRotator(0, TargetYaw, 0);
		const FRotator& ActorRotation = GetPawn()->GetActorRotation();

		const FRotator& NewRotation = FQuat::Slerp(ActorRotation.Quaternion(), TargetRotator.Quaternion(),
		                                           RotationSpeed * DeltaTime).Rotator();
		SetControlRotation(FRotator(0, NewRotation.Yaw, 0));
		float YawDelta = NewRotation.Yaw - ActorRotation.Yaw;
		if (const auto& C = Cast<ATRXCharacterBase>(GetPawn()))
		{
			C->SetYawDelta(YawDelta / DeltaTime);
		}
		if (DebugTrace)
		{
			FString msg;
			msg.AppendInt(TargetYaw);
			GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Red, msg);
			DrawDebugLine(GetWorld(), GetPawn()->GetActorLocation(),
			              GetPawn()->GetActorLocation() + ActorRotation.Vector() * 300, FColor::Red, false, 0);
			auto HitResult = GetCursorLoc();
			auto tr = FRotationMatrix::MakeFromX(HitResult.Location - GetPawn()->GetActorLocation()).Rotator().Yaw;
			DrawDebugLine(GetWorld(), GetPawn()->GetActorLocation(),
			              GetPawn()->GetActorLocation() + FRotator(0, tr, 0).Vector() * 300, FColor::Green, false, 0);
		}


		/*INTERACTION*/

		
	}
	

	
}

void ATRXPlayerControllerBase::GetAudioListenerPosition(FVector& OutLocation, FVector& OutFrontDir,
                                                        FVector& OutRightDir) const
{
	Super::GetAudioListenerPosition(OutLocation, OutFrontDir, OutRightDir);
	if (GetPawn())
	{
		const auto& tr = GetPawn()->GetTransform();
		OutLocation = tr.GetLocation();
		OutFrontDir = FVector(1, 0, 0);
		OutRightDir = FVector(0, -1, 0);
	}
}

void ATRXPlayerControllerBase::TryInteract(const FInputActionValue& Value)
{
	InteractionComponent->TryInteract();
}

void ATRXPlayerControllerBase::ActivateAbility1(const FInputActionValue& Value)
{
	if (auto ASC = GetPlayerState<ATRXPlayerState>()->GetAbilitySystemComponent())
		ASC->PressInputID(static_cast<int32>(EAbilityInputID::Ability1));
}

void ATRXPlayerControllerBase::ActivateAbility2(const FInputActionValue& Value)
{
	if (auto ASC = GetPlayerState<ATRXPlayerState>()->GetAbilitySystemComponent())
		ASC->PressInputID(static_cast<int32>(EAbilityInputID::Ability2));
}

void ATRXPlayerControllerBase::ActivateAbility3(const FInputActionValue& Value)
{
	if (auto ASC = GetPlayerState<ATRXPlayerState>()->GetAbilitySystemComponent())
		ASC->PressInputID(static_cast<int32>(EAbilityInputID::Ability3));
}

void ATRXPlayerControllerBase::ActivateAbility4(const FInputActionValue& Value)
{
	if (auto ASC = GetPlayerState<ATRXPlayerState>()->GetAbilitySystemComponent())
		ASC->PressInputID(static_cast<int32>(EAbilityInputID::Ability4));
}

void ATRXPlayerControllerBase::CancelAbility1(const FInputActionValue& Value)
{
	if (auto ASC = GetPlayerState<ATRXPlayerState>()->GetAbilitySystemComponent())
		ASC->ReleaseInputID(static_cast<int32>(EAbilityInputID::Ability1));
}

void ATRXPlayerControllerBase::CancelAbility2(const FInputActionValue& Value)
{
	if (auto ASC = GetPlayerState<ATRXPlayerState>()->GetAbilitySystemComponent())
		ASC->ReleaseInputID(static_cast<int32>(EAbilityInputID::Ability2));
}

void ATRXPlayerControllerBase::CancelAbility3(const FInputActionValue& Value)
{
	if (auto ASC = GetPlayerState<ATRXPlayerState>()->GetAbilitySystemComponent())
		ASC->ReleaseInputID(static_cast<int32>(EAbilityInputID::Ability3));
}

void ATRXPlayerControllerBase::CancelAbility4(const FInputActionValue& Value)
{
	if (auto ASC = GetPlayerState<ATRXPlayerState>()->GetAbilitySystemComponent())
		ASC->ReleaseInputID(static_cast<int32>(EAbilityInputID::Ability4));
}


// void ATRXPlayerControllerBase::Ability1Input(const FInputActionValue& Value)
// {
// 	if(auto ASC = GetPlayerState<ATRXPlayerState>()->GetAbilitySystemComponent())
// 	{
// 		if(Value.Get<bool>())
// 		{
// 			ASC->PressInputID(static_cast<int32>(EAbilityInputID::Ability1));
// 		}
// 		else
// 		{
// 			ASC->ReleaseInputID(static_cast<int32>(EAbilityInputID::Ability1));
// 		}
// 	}
// }
//
// void ATRXPlayerControllerBase::Ability2Input(const FInputActionValue& Value)
// {
// 	if(auto ASC = GetPlayerState<ATRXPlayerState>()->GetAbilitySystemComponent())
// 	{
// 		bool bCond = Value.Get<bool>();
// 		if(bCond)
// 		{
// 			ASC->PressInputID(static_cast<int32>(EAbilityInputID::Ability2));
// 		}
// 		else
// 		{
// 			ASC->ReleaseInputID(static_cast<int32>(EAbilityInputID::Ability2));
// 		}
// 	}
// }
//
// void ATRXPlayerControllerBase::Ability3Input(const FInputActionValue& Value)
// {
// 	if(auto ASC = GetPlayerState<ATRXPlayerState>()->GetAbilitySystemComponent())
// 	{
// 		if(Value.Get<bool>())
// 		{
// 			ASC->PressInputID(static_cast<int32>(EAbilityInputID::Ability3));
// 		}
// 		else
// 		{
// 			ASC->ReleaseInputID(static_cast<int32>(EAbilityInputID::Ability3));
// 		}
// 	}
// }
//
// void ATRXPlayerControllerBase::Ability4Input(const FInputActionValue& Value)
// {
// 	if(auto ASC = GetPlayerState<ATRXPlayerState>()->GetAbilitySystemComponent())
// 	{
// 		if(Value.Get<bool>())
// 		{
// 			ASC->PressInputID(static_cast<int32>(EAbilityInputID::Ability4));
// 		}
// 		else
// 		{
// 			ASC->ReleaseInputID(static_cast<int32>(EAbilityInputID::Ability4));
// 		}
// 	}
// }

EControlMode ATRXPlayerControllerBase::GetControlMode() const
{
	return ControlMode;
}

void ATRXPlayerControllerBase::SetControlMode(EControlMode NewControlMode)
{
	this->ControlMode = NewControlMode;
}

void ATRXPlayerControllerBase::TransferItem_Implementation(UTRXInventoryComponent* from, UTRXInventoryComponent* to, UTRXInventoryObject* Item, const FGridCoord& Position)
{
	if (!from || !to || !Item)
		return;
	if (from->ContainsItem(Item))
	{
		if (from != to)
		{
			if (to->AddItemAtPosition(Item, Position))
			{
				from->RemoveItem(Item);
			}
		}
		else
		{
			from->MoveItem(Item, Position);
		}
	}
}

void ATRXPlayerControllerBase::Internal_Move(const FInputActionValue& Value) const
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector MoveDirection = FVector(MovementVector.Y, MovementVector.X, 0.0f);
		ControlledPawn->AddMovementInput(MoveDirection);
	}
}

void ATRXPlayerControllerBase::Move(const FInputActionValue& Value)
{
	Internal_Move(Value);
}

FHitResult ATRXPlayerControllerBase::GetCursorLoc()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	return HitResult;
}
