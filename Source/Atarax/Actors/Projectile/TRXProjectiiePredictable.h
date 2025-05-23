﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TRXProjectiiePredictable.generated.h"

UCLASS()
class ATARAX_API ATRXProjectiiePredictable : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATRXProjectiiePredictable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
