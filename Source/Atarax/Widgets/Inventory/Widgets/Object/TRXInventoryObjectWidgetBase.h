// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TRXInventoryObjectWidgetBase.generated.h"

class USizeBox;
class UTRXInventoryComponent;
class UTRXInventoryObject;
/**
 * 
 */
UCLASS()
class ATARAX_API UTRXInventoryObjectWidgetBase : public UUserWidget
{
public:
	const TObjectPtr<UTRXInventoryObject>& GetInventoryObject() const;
	void SetInventoryObject(const TObjectPtr<UTRXInventoryObject>& InInventoryObject);
	const TObjectPtr<UTRXInventoryComponent>& GetInventoryComponent() const;
	void SetInventoryComponent(const TObjectPtr<UTRXInventoryComponent>& InInventoryComponent);

private:
	GENERATED_BODY()

	virtual void NativeConstruct() override;
	
private:
	UPROPERTY(BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess=true, ExposeOnSpawn=true))
	TObjectPtr<UTRXInventoryObject> InventoryObject;
	UPROPERTY(BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess=true, ExposeOnSpawn=true))
	TObjectPtr<UTRXInventoryComponent> InventoryComponent;
	UPROPERTY(BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess=true, BindWidget))
	USizeBox* SizeBox_Bind;

	int SizeX;
	int SizeY;
	bool Rotated;
	int PosX;
	int PosY;
};
