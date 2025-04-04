// Fill out your copyright notice in the Description page of Project Settings.


#include "TRXInventoryObject.h"

#include "Atarax/Common/Helpers/TRXHelpers.h"
#include "Net/UnrealNetwork.h"

void UTRXInventoryObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Prepon, COND_None, REPNOTIFY_Always);
}

class UWorld* UTRXInventoryObject::GetWorld() const
{
	return GetOuter()->GetWorld();
}

void UTRXInventoryObject::hut()
{
	UTRXHelpers::PrintString(GetWorld(),FString(GetClass()->GetDisplayNameText().ToString()));
}	
