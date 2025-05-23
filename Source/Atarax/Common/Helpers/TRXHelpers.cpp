﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "TRXHelpers.h"

#include "Atarax/InventorySysem/TRXInventoryObject.h"

void UTRXHelpers::PrintString(UObject* WorldContext, FString InStr, float time, FColor Color, int key)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull);
	FString Prefix;
	if (World)
	{
		if (World->WorldType == EWorldType::PIE)
		{
			switch(World->GetNetMode())
			{
			case NM_Client:
				// GPlayInEditorID 0 is always the server, so 1 will be first client.
					// You want to keep this logic in sync with GeneratePIEViewportWindowTitle and UpdatePlayInEditorWorldDebugString
						Prefix = FString(TEXT("Client %d: "), GPlayInEditorID);
				break;
			case NM_DedicatedServer:
			case NM_ListenServer:
				Prefix = FString(TEXT("Server: "));
				break;
			case NM_Standalone:
				break;
			}
		}
		FString DebugMessage = FString(Prefix + InStr);
		GEngine->AddOnScreenDebugMessage(key, time, Color, DebugMessage);
	}
}

FGridCoord UTRXHelpers::PixelToGrid(const FVector2d& Coord, int GridSize)
{
	int x = FMath::Floor(Coord.X / GridSize);
	int y = FMath::Floor(Coord.Y / GridSize);
 
	return FGridCoord(x, y);
}
