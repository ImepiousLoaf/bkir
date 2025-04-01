// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TRXInventoryComponent.generated.h"


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
	void MakeObjectToRep(int a);
	
private:
	UFUNCTION()
	void onObjRep(UTRXInventoryObject* Old);
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess = true), ReplicatedUsing= onObjRep)
	TObjectPtr<UTRXInventoryObject> ObjectToRep;
};
