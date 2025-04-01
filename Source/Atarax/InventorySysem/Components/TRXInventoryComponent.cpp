// Fill out your copyright notice in the Description page of Project Settings.


#include "TRXInventoryComponent.h"

#include "Atarax/InventorySysem/TRXInventoryObject.h"
#include "Engine/ActorChannel.h"
#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
UTRXInventoryComponent::UTRXInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bReplicateUsingRegisteredSubObjectList = true;
	SetIsReplicatedByDefault(true);
	// ...
}


// Called when the game starts
void UTRXInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	
}

bool UTRXInventoryComponent::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{

	bool bWroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);
		
	// Single Object
	bWroteSomething |= Channel->ReplicateSubobject(ObjectToRep, *Bunch, *RepFlags);
	return bWroteSomething;
		
	// Array of Objects
	//bWroteSomething |= Channel->ReplicateSubobjectList(ArrayOfMyObject, *Bunch, *RepFlags);
		
}

void UTRXInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, ObjectToRep, COND_None, REPNOTIFY_Always);
}


// Called every frame
void UTRXInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTRXInventoryComponent::MakeObjectToRep(int a)
{
	if(ObjectToRep)
		RemoveReplicatedSubObject(ObjectToRep);
	
	ObjectToRep= NewObject<UTRXInventoryObject>();
	ObjectToRep->Prepon = a;
	AddReplicatedSubObject(ObjectToRep);
}

void UTRXInventoryComponent::onObjRep(UTRXInventoryObject* Old)
{
	FString str("prepon replicated: ");
	str.AppendInt(Old ? Old->Prepon : 0);
	GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Orange, str);
}

