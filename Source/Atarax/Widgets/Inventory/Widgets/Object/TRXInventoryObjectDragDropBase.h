// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Atarax/InventorySysem/TRXInventoryObject.h"
#include "Blueprint/DragDropOperation.h"
#include "TRXInventoryObjectDragDropBase.generated.h"

class UTRXInventoryComponent;
/**
 * 
 */
UCLASS()
class ATARAX_API UTRXInventoryObjectDragDropBase : public UDragDropOperation
{
public:
	TObjectPtr<UTRXInventoryComponent> GetInventoryComponent() const;
	TObjectPtr<UTRXInventoryObject> GetInventoryObject() const;

	
private:
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess=true, ExposeOnSpawn))
	TObjectPtr<UTRXInventoryComponent> InventoryComponent;
	UPROPERTY(BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess=true, ExposeOnSpawn))
	TObjectPtr<UTRXInventoryObject> InventoryObject;
	UPROPERTY(BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess=true, ExposeOnSpawn))
	FGridCoord GrabPoint;
};
