// Fill out your copyright notice in the Description page of Project Settings.


#include "TRXInventoryObjectDragDropBase.h"

TObjectPtr<UTRXInventoryComponent> UTRXInventoryObjectDragDropBase::GetInventoryComponent() const
{
	return InventoryComponent;
}

TObjectPtr<UTRXInventoryObject> UTRXInventoryObjectDragDropBase::GetInventoryObject() const
{
	return InventoryObject;
}
