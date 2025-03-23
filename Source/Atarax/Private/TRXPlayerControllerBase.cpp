#include "TRXPlayerControllerBase.h"
#include "TRXCharacterBase.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"

ATRXPlayerControllerBase::ATRXPlayerControllerBase()
{
	bShowMouseCursor = false;
}

void ATRXPlayerControllerBase::Zoom_Implementation(const FInputActionValue& Value)
{
}

void ATRXPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
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
	}
}

void ATRXPlayerControllerBase::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void ATRXPlayerControllerBase::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (APawn* ControlledPawn = GetPawn())
	{
		FVector MoveDirection = FVector(MovementVector.Y, MovementVector.X, 0.0f);
		ControlledPawn->AddMovementInput(MoveDirection);
	}
}

FHitResult ATRXPlayerControllerBase::GetCursorLoc()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	return HitResult;
}

