// Fill out your copyright notice in the Description page of Project Settings.


#include "TRXInventoryObjectWidgetBase.h"

#include "Atarax/InventorySysem/TRXInventoryObject.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"

#pragma optimize("", off)

const TObjectPtr<UTRXInventoryObject>& UTRXInventoryObjectWidgetBase::GetInventoryObject() const
{
	return InventoryObject;
}

void UTRXInventoryObjectWidgetBase::SetInventoryObject(const TObjectPtr<UTRXInventoryObject>& InInventoryObject)
{
	this->InventoryObject = InInventoryObject;
}

const TObjectPtr<UTRXInventoryComponent>& UTRXInventoryObjectWidgetBase::GetInventoryComponent() const
{
	return InventoryComponent;
}

void UTRXInventoryObjectWidgetBase::SetInventoryComponent(
	const TObjectPtr<UTRXInventoryComponent>& InInventoryComponent)
{
	this->InventoryComponent = InInventoryComponent;
}

void UTRXInventoryObjectWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
	if (InventoryObject)
	{
		SizeX = InventoryObject->Width;
		SizeY = InventoryObject->Height;
		PosX = InventoryObject->CoordX;
		PosY = InventoryObject->CoordY;
		Rotated = InventoryObject->Rotated;
		if (SizeBox_Bind)
		{
			if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(this->Slot))
			{
				CanvasPanelSlot->SetSize(Rotated ? FVector2d(SizeY, SizeX) * 64 : FVector2d(SizeX, SizeY) * 64);
				CanvasPanelSlot->SetPosition(FVector2d(PosX, PosY) * 64);
			}
		}
	}
}
