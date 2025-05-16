// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Atarax/GMPSC/GameInstance/TRXInventorySubsystem.h"
#include "Components/ActorComponent.h"
#include "TRXInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInventoryUpdated);


struct FGridCoord;
class UTRXInventoryObject;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ATARAX_API UTRXInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTRXInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	bool AddItem(UTRXInventoryObject* Item);
	UFUNCTION(BlueprintCallable)
	bool RemoveItem(UTRXInventoryObject* Item);
	UFUNCTION(BlueprintCallable)
	bool AddItemAtPosition(UTRXInventoryObject* Item, const FGridCoord& Position);
	UFUNCTION(Blueprintable)
	bool ContainsItem(UTRXInventoryObject* Item) const;
	UFUNCTION(Blueprintable)
	bool IsValidPosition(UTRXInventoryObject* Item, FGridCoord Position) const;
	UFUNCTION(Blueprintable)
	bool MoveItem(UTRXInventoryObject* Item, const FGridCoord& position) const;


	UFUNCTION()
	void Onrepy();
	FVector2d GetSize() const;
	const TArray<UTRXInventoryObject*>& GetInventoryArray() const;
private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess = true), ReplicatedUsing=Onrepy)
	TArray<UTRXInventoryObject*> InventoryArray;
	UPROPERTY(ReplicatedUsing=Onrepy)
	mutable int8 ChangedArray = true;
	UPROPERTY(BlueprintAssignable, meta=(AllowPrivateAccess = true))
	FInventoryUpdated OnInventoryUpdated;

	UFUNCTION()
	void SendInventoryUpdated() const;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(AllowPrivateAccess = true), Replicated)
	int SizeX;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(AllowPrivateAccess = true), Replicated)
	int SizeY;

};


