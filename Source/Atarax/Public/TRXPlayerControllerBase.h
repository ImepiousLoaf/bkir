#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "TRXPlayerControllerBase.generated.h"

UCLASS()
class ATRXPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	ATRXPlayerControllerBase();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Zoom(const FInputActionValue& Value);
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;
	
private:
	void Move(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	FHitResult GetCursorLoc();

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* MoveAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ZoomAction;
};