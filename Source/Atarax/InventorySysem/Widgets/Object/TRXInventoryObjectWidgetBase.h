// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TRXInventoryObjectWidgetBase.generated.h"

class UTRXInventoryObject;
/**
 * 
 */
UCLASS()
class ATARAX_API UTRXInventoryObjectWidgetBase : public UUserWidget
{
	GENERATED_BODY()


private:
	UPROPERTY(BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess=true, ExposeOnSpawn=true))
	TObjectPtr<UTRXInventoryObject> InventoryObject;
};
