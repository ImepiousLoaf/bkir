// Fill out your copyright notice in the Description page of Project Settings.


#include "TRXInventoryObject.h"

#include "Atarax/Common/Helpers/TRXHelpers.h"
#include "Net/UnrealNetwork.h"

UTRXInventoryObject::UTRXInventoryObject()
{
	
}

void UTRXInventoryObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Prepon, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME(ThisClass, CoordX);
	DOREPLIFETIME(ThisClass, CoordY);
	DOREPLIFETIME(ThisClass, Quantity);
	DOREPLIFETIME(ThisClass, Rotated);
}

class UWorld* UTRXInventoryObject::GetWorld() const
{
	return GetOuter()->GetWorld();
}

void UTRXInventoryObject::hut()
{
	UTRXHelpers::PrintString(GetWorld(),FString(GetClass()->GetDisplayNameText().ToString()));
}	
