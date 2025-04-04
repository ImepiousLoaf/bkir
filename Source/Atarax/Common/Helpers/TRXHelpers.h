// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TRXHelpers.generated.h"

/**
 * 
 */
UCLASS()
class ATARAX_API UTRXHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static void PrintString(UObject* WorldContext, FString InStr, float time = 2.0f, FColor Color = FColor(160, 108, 255), int key = -1);
};
