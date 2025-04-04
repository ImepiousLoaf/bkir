// Fill out your copyright notice in the Description page of Project Settings.


#include "TRXInventorySubsystem.h"

void UTRXInventorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	{
		char T[] =
		{
			'0', '0', '0', '0',
			'0', '0', '0', '0',
			'0', '0', '0', '0',
			'0', '0', '0', '0',
		};

		Templates.Add(FString("Test"), FTRXInventoryTemplate(4, 4, T));
	}
}

void UTRXInventorySubsystem::Deinitialize()
{
	Super::Deinitialize();
	Templates.Empty();
}
