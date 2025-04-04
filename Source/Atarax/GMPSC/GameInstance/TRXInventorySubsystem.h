// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TRXInventorySubsystem.generated.h"

USTRUCT(BlueprintType)
struct FTRXInventoryTemplate
{
	GENERATED_BODY()
	FTRXInventoryTemplate() {Width = 0; Height = 0;}
	FTRXInventoryTemplate(int w, int h, char arr[])
	{
		Width = w;
		Height = h;
		Template.Empty();
		for (int y = 0; y < h; y++)
		{
			for (int x = 0; x < w; x++)
			{
				if (const char Char = arr[y * h + x]; Char != ' ')
				{
					const int Layer = Char - '0';
					Template.Add(FIntVector(x,y,Layer));
				} else
				{
					Template.Add(FIntVector(x,y,-1));
				}
			}
		}
	}
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Inventory")
	int Width;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Inventory")
	int Height;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Inventory")
	TArray<FIntVector> Template;
};


/**
 * 
 */
UCLASS()
class ATARAX_API UTRXInventorySubsystem : public UGameInstanceSubsystem
{
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;


	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FTRXInventoryTemplate> Templates;
	
	GENERATED_BODY()
};
