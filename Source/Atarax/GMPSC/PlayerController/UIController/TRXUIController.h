// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TRXUIController.generated.h"


class UTRXHUDWidgetBase;
class UTRXInventoryGridWidgetBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ATARAX_API UTRXUIController : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTRXUIController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void ToggleWidget(UUserWidget* Widget);
	void HideWidget();
	void ShowWidget(UUserWidget* Widget);
	UFUNCTION(BlueprintCallable)
	void SetWidget(UUserWidget* Widget);
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = UI, meta = (AllowPrivateAccess = "true"))
	UUserWidget* CurrentWidget;
};
