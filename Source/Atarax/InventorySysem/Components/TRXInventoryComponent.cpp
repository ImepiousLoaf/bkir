// Fill out your copyright notice in the Description page of Project Settings.


#include "TRXInventoryComponent.h"

#include "Atarax/InventorySysem/TRXInventoryObject.h"
#include "Engine/ActorChannel.h"
#include "Net/UnrealNetwork.h"

#pragma optimize("", off)
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
	//bWroteSomething |= Channel->ReplicateSubobjectList(InventoryArray, *Bunch, *RepFlags);
	return bWroteSomething;
		
	// Array of Objects
	//bWroteSomething |= Channel->ReplicateSubobjectList(ArrayOfMyObject, *Bunch, *RepFlags);
		
}

void UTRXInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, InventoryArray, COND_None, REPNOTIFY_Always);
}


// Called every frame
void UTRXInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UTRXInventoryComponent::AddItem(UTRXInventoryObject* Item)
{
	struct aabb
	{
		int8 Xmin, Xmax, Ymin, Ymax;
		bool intersect(const aabb& other) const
		{
			for (int i = 0; i < 4; i++)
			{
				bool bCond0 = Xmin < other.Xmax;
				bool bCond1 = Xmax > other.Xmin;
				bool bCond2 = Ymin < other.Ymax;
				bool bCond3 = Ymax > other.Ymin;
				if (bCond0 && bCond1 &&
					bCond2 && bCond3)
				{
					return true;
				}
			}
			return false;
		}
		aabb(const UTRXInventoryObject* obj)
		{
			if (obj->Rotated)
			{
				Xmin = obj->CoordX;
				Ymin = obj->CoordY;
				Xmax = obj->CoordX + obj->Width;
				Ymax = obj->CoordY + obj->Height;
				return;
			}
			Xmin = obj->CoordX;
			Ymin = obj->CoordY;
			Xmax = obj->CoordX + obj->Width;
			Ymax = obj->CoordY + obj->Height;
		}
	};
	TArray<aabb> boundings;
	for (const auto& it : InventoryArray)
	{
		boundings.Add(aabb(it));
	}
	for (int j = 0; j < SizeY - Item->Height + 1; j++)
	{
		for (int i = 0; i < SizeX - Item->Width + 1; i++)
		{
			Item->CoordX = i;
			Item->CoordY = j;
			aabb aba(Item);
			bool found = true;
			for (const aabb& it : boundings)
			{
				if (aba.intersect(it))
				{
					found = false;
					break;
				}
			}
			if (found)
			{
				InventoryArray.Add(Item);
				return true;
			}
		}
	}
	Item->CoordX = 0;
	Item->CoordY = 0;
	return false;
}
