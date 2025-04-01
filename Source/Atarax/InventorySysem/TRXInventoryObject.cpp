// Fill out your copyright notice in the Description page of Project Settings.


#include "TRXInventoryObject.h"

#include "Net/UnrealNetwork.h"

void UTRXInventoryObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Prepon, COND_None, REPNOTIFY_Always);
}

void UTRXInventoryObject::hut()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "pipa");
}	
