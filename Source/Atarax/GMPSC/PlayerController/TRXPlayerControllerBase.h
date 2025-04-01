#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Atarax/AbilitySystem/Abilities/TRXBaseAbility.h"
#include "TRXPlayerControllerBase.generated.h"

UENUM(BlueprintType, Category="Input")
enum EControlMode
{
	FreeRotation,
	TowardControl,
};

UCLASS()
class ATRXPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
public:
	
	ATRXPlayerControllerBase();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Zoom(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category="Input")
	EControlMode GetControlMode() const;
	UFUNCTION(BlueprintCallable, Category="Input")
	void SetControlMode(EControlMode ControlMode);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void GetAudioListenerPosition(FVector& OutLocation, FVector& OutFrontDir, FVector& OutRightDir) const override;

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Movement", meta=(AllowPrivateAccess = true))
	float RotationSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Movement", meta=(AllowPrivateAccess = true))
	bool DebugTrace;
	void Ability1Input(const FInputActionValue& Value);
	void Ability2Input(const FInputActionValue& Value);
	void Ability3Input(const FInputActionValue& Value);
	void Ability4Input(const FInputActionValue& Value);
	void GetTargetControl(float& Yaw, float& Pitch);
	void Move(const FInputActionValue& Value);
	void Internal_Move(const FInputActionValue& Value) const;
	UFUNCTION(BlueprintCallable)
	FHitResult GetCursorLoc();
	EControlMode ControlMode;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* MoveAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ZoomAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* Ability1;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* Ability2;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* Ability3;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* Ability4;
};