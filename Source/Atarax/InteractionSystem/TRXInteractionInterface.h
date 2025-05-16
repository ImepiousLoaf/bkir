// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TRXInteractionInterface.generated.h"

class UTRXUIController;
/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UTRXInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class ATARAX_API ITRXInteractionInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(Category = "Interaction")
	virtual bool CanInteract(AActor* Interactor) const = 0;

	UFUNCTION(Category = "Interaction")
	virtual void InteractClient(AActor* Interactor) = 0;
	
	UFUNCTION(Category = "Interaction")
	virtual void InteractServer(AActor* Interactor) = 0;
	
	UFUNCTION(Category = "Interaction")
	virtual void Highlight(bool bEnable) = 0;
	
protected:
	UFUNCTION(Category = "Interaction|System")
	virtual UPrimitiveComponent* GetMesh() = 0;

	UFUNCTION(Category = "Interaction|System")
	virtual UPrimitiveComponent* GetCollider() = 0;
};