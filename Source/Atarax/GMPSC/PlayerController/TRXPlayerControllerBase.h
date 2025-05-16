#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Atarax/AbilitySystem/Abilities/TRXBaseAbility.h"
#include "Atarax/InteractionSystem/TRXInteractionComponent.h"
#include "UIController/TRXUIController.h"
#include "TRXPlayerControllerBase.generated.h"

class UTRXInventoryObject;
class UTRXInventoryComponent;

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

	UFUNCTION(BlueprintCallable, Server, Unreliable, Category="Inventory")
	void TransferItem(UTRXInventoryComponent* from, UTRXInventoryComponent* to, UTRXInventoryObject* Item, const FGridCoord& Position);
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void GetAudioListenerPosition(FVector& OutLocation, FVector& OutFrontDir, FVector& OutRightDir) const override;

	UPROPERTY(BlueprintReadOnly, Category="Interact", meta=(AllowPrivateAccess=true))
	UTRXInteractionComponent* InteractionComponent;
	UPROPERTY(BlueprintReadOnly, Category="UI", meta=(AllowPrivateAccess=true))
	UTRXUIController* UIComponent;

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Movement", meta=(AllowPrivateAccess = true))
	float RotationSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Movement", meta=(AllowPrivateAccess = true))
	bool DebugTrace;
	

	void TryInteract(const FInputActionValue& Value);
	
	void ActivateAbility1(const FInputActionValue& Value);
	void ActivateAbility2(const FInputActionValue& Value);
	void ActivateAbility3(const FInputActionValue& Value);
	void ActivateAbility4(const FInputActionValue& Value);
	
	void CancelAbility1(const FInputActionValue& Value);
	void CancelAbility2(const FInputActionValue& Value);
	void CancelAbility3(const FInputActionValue& Value);
	void CancelAbility4(const FInputActionValue& Value);

	

	//old ability functions
	// void Ability1Input(const FInputActionValue& Value);
	// void Ability2Input(const FInputActionValue& Value);
	// void Ability3Input(const FInputActionValue& Value);
	// void Ability4Input(const FInputActionValue& Value);
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
	class UInputAction* InteractAction;
	
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