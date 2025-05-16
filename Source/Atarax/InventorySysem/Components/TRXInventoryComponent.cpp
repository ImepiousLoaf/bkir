// Fill out your copyright notice in the Description page of Project Settings.


#include "TRXInventoryComponent.h"

#include "Atarax/Common/Helpers/TRXHelpers.h"
#include "Atarax/InventorySysem/TRXInventoryObject.h"
#include "Engine/ActorChannel.h"
#include "Net/UnrealNetwork.h"

 #pragma optimize("", off)



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
	aabb(const UTRXInventoryObject* obj, FGridCoord& Position)
	{
		if (obj->Rotated)
		{
			Xmin = Position.X;
			Ymin = Position.Y;
			Xmax = Position.X + obj->Width;
			Ymax = Position.Y + obj->Height;
			return;
		}
		Xmin = Position.X;
		Ymin = Position.Y;
		Xmax = Position.X + obj->Width;
		Ymax = Position.Y + obj->Height;
	}
};



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
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, ChangedArray, COND_None, REPNOTIFY_Always);
}


// Called every frame
void UTRXInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UTRXInventoryComponent::AddItem(UTRXInventoryObject* Item)
{
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
				if (auto DubObject = DuplicateObject<UTRXInventoryObject>(Item, GetOwner())){
					GetOwner()->AddReplicatedSubObject(DubObject, COND_None);
					InventoryArray.Add(DubObject);
					SendInventoryUpdated();
					return true;
				}
			}
		}
	}
	Item->CoordX = 0;
	Item->CoordY = 0;
	return false;
}

bool UTRXInventoryComponent::RemoveItem(UTRXInventoryObject* Item)
{
	if (InventoryArray.Contains(Item))
	{
		GetOwner()->RemoveReplicatedSubObject(Item);
		InventoryArray.RemoveSwap(Item);
		SendInventoryUpdated();
		return true;
	}
	return false;
}

bool UTRXInventoryComponent::AddItemAtPosition(UTRXInventoryObject* Item, const FGridCoord& Position)
{
	if (const bool A = IsValidPosition(Item, Position))
	{
		Item->CoordX = Position.X;
		Item->CoordY = Position.Y;
		AddReplicatedSubObject(Item);
		InventoryArray.Add(Item);
		SendInventoryUpdated();
		return true;
	}
	return false;
}

bool UTRXInventoryComponent::IsValidPosition(UTRXInventoryObject* Item, FGridCoord Position) const
{
	TArray<aabb> boundings;
	for (const auto& it : InventoryArray)
	{
		if (it != Item)
			boundings.Add(aabb(it));
	}

	aabb aba(Item, Position);

	if (aba.Xmax > SizeX || aba.Ymax > SizeY || aba.Xmin < 0 || aba.Ymin < 0)
	{
		return false;
	}
	bool valid = true;
	for (const aabb& it : boundings)
	{
		if (it.intersect(aba))
			valid = false;
	}
	UTRXHelpers::PrintString(GetWorld(), valid ? "valid" : "invalid");
	return valid;
}
bool UTRXInventoryComponent::MoveItem(UTRXInventoryObject* Item, const FGridCoord& position) const
{
	if (IsValidPosition(Item, position))
	{
		Item->CoordX = position.X;
		Item->CoordY = position.Y;
		SendInventoryUpdated();
		return true;
	}
	return false;
}

void UTRXInventoryComponent::Onrepy()
{
	UTRXHelpers::PrintString(GetWorld(), "Onrepy");
	OnInventoryUpdated.Broadcast();
}


bool UTRXInventoryComponent::ContainsItem(UTRXInventoryObject* Item) const
{
	return InventoryArray.Contains(Item);
}

FVector2d UTRXInventoryComponent::GetSize() const
{
	return FVector2d(SizeX, SizeY);
}

const TArray<UTRXInventoryObject*>& UTRXInventoryComponent::GetInventoryArray() const
{
	return InventoryArray;
}

void UTRXInventoryComponent::SendInventoryUpdated() const
{
	ChangedArray++;
	OnInventoryUpdated.Broadcast();
}

// void UTRXInventoryComponent::SendInventoryUpdated_Implementation() const
// {
// 	UTRXHelpers::PrintString(GetWorld(), "SendInventoryUpdated");
// 	//ChangedArray++;
// 	//OnInventoryUpdated.Broadcast();
// }
