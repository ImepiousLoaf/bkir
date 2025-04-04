// Fill out your copyright notice in the Description page of Project Settings.


#include "TRXHelpers.h"

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
						Prefix = FString::Printf(TEXT("Client %d: "), GPlayInEditorID);
				break;
			case NM_DedicatedServer:
			case NM_ListenServer:
				Prefix = FString::Printf(TEXT("Server: "));
				break;
			case NM_Standalone:
				break;
			}
		}
		GEngine->AddOnScreenDebugMessage(key, time, Color, FString(Prefix + InStr));
	}
}
