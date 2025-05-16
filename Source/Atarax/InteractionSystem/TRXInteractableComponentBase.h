// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TRXInteractableComponentBase.generated.h"


class ATRXPlayerControllerBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ATARAX_API UTRXInteractableComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTRXInteractableComponentBase();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
