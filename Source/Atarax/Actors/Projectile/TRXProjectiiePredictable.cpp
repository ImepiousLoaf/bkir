// Fill out your copyright notice in the Description page of Project Settings.


#include "TRXProjectiiePredictable.h"


// Sets default values
ATRXProjectiiePredictable::ATRXProjectiiePredictable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATRXProjectiiePredictable::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ATRXProjectiiePredictable::IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const
{
	bool A = Super::IsNetRelevantFor(RealViewer, ViewTarget, SrcLocation);
	bool B = true;
	if(const auto InstigatorPlayerController = GetInstigator()->GetController())
	{
		B = InstigatorPlayerController != RealViewer;
	}
	return A && B;
}

// Called every frame
void ATRXProjectiiePredictable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

