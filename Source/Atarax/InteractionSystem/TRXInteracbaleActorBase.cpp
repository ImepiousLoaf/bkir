// Fill out your copyright notice in the Description page of Project Settings.


#include "TRXInteracbaleActorBase.h"

#include "TRXInteractableComponentBase.h"

// Sets default values
ATRXInteracbaleActorBase::ATRXInteracbaleActorBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CreateDefaultSubobject<UTRXInteractableComponentBase>(TEXT("InteractableComponent"));
}

bool ATRXInteracbaleActorBase::CanInteract(AActor* Interactor) const
{
	return true;
}

void ATRXInteracbaleActorBase::InteractClient(AActor* Interactor)
{
}

void ATRXInteracbaleActorBase::InteractServer(AActor* Interactor)
{
}

void ATRXInteracbaleActorBase::Highlight(bool bEnable)
{
}

UPrimitiveComponent* ATRXInteracbaleActorBase::GetMesh()
{
	return nullptr;
}

UPrimitiveComponent* ATRXInteracbaleActorBase::GetCollider()
{
	return nullptr;
}

// Called when the game starts or when spawned
void ATRXInteracbaleActorBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATRXInteracbaleActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

