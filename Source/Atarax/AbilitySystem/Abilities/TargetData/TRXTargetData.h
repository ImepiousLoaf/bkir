#pragma once
#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "TRXTargetData.generated.h"

USTRUCT()
struct FLocationData
{
	GENERATED_BODY()
	
	UPROPERTY()
	FVector LocationA;
	UPROPERTY()
	FVector LocationB;
	UPROPERTY()
	FRotator Rotation;
};


USTRUCT(BlueprintType)
struct FTRXTargetData : public FGameplayAbilityTargetData
{
	GENERATED_BODY()
public:

	FTRXTargetData()
	{ }

	UPROPERTY(BlueprintReadWrite)
	FVector LocationA;
	UPROPERTY(BlueprintReadWrite)
	FVector LocationB;
	UPROPERTY(BlueprintReadWrite)
	FRotator Rotation;

	UPROPERTY()
	FPredictionKey PredictionKey;

	// This is required for all child structs of FGameplayAbilityTargetData
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FTRXTargetData::StaticStruct();
	}

	// This is required for all child structs of FGameplayAbilityTargetData
	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
	{
		// The engine already defined NetSerialize for FName & FPredictionKey, thanks Epic!
		LocationA.NetSerialize(Ar, Map, bOutSuccess);
		LocationB.NetSerialize(Ar, Map, bOutSuccess);
		Rotation.NetSerialize(Ar, Map, bOutSuccess);
		PredictionKey.NetSerialize(Ar, Map, bOutSuccess);
		bOutSuccess = true;
		return true;
	}
	
	static FGameplayAbilityTargetDataHandle MakeTargetDataFromLocation(const FVector& LocationA, const FVector& LocationB, const FRotator& Rotation)
	{
		// Create our target data type, 
		// Handle's automatically cleanup and delete this data when the handle is destructed, 
		// if you don't add this to a handle then be careful because this deals with memory management and memory leaks so its safe to just always add it to a handle at some point in the frame!
		FTRXTargetData* MyCustomData = new FTRXTargetData();
		// Setup the struct's information to use the inputted name and any other changes we may want to do
		MyCustomData->LocationA = LocationA;
		MyCustomData->LocationB = LocationB;
		MyCustomData->Rotation = Rotation;
	
		// Make our handle wrapper for Blueprint usage
		FGameplayAbilityTargetDataHandle Handle;
		// Add the target data to our handle
		Handle.Add(MyCustomData);
		// Output our handle to Blueprint
		return Handle;
	}
	
	static FLocationData GetLocationFromTargetData(const FGameplayAbilityTargetDataHandle& Handle, const int Index)
	{   
		// NOTE, there is two versions of this '::Get(int32 Index)' function; 
		// 1) const version that returns 'const FGameplayAbilityTargetData*', good for reading target data values 
		// 2) non-const version that returns 'FGameplayAbilityTargetData*', good for modifying target data values
		const FGameplayAbilityTargetData* Data = Handle.Get(Index); // This will valid check the index for you 
    
		// Valid check we have something to use, null data means nothing to cast for
		if(Data == nullptr)
		{
			return FLocationData();
		}
		// This is basically the type checking pass, static_cast does not have type safety, this is why we do this check.
		// If we don't do this then it will object slice the struct and thus we have no way of making sure its that type.
		if(Data->GetScriptStruct() == FTRXTargetData::StaticStruct())
		{
			// Here is when you would do the cast because we know its the correct type already
			const FTRXTargetData* CustomData = static_cast<const FTRXTargetData*>(Data);    
			return FLocationData{CustomData->LocationA, CustomData->LocationB, CustomData->Rotation};
		}
		return FLocationData();
	}
};

template<>
struct TStructOpsTypeTraits<FTRXTargetData> : public TStructOpsTypeTraitsBase2<FTRXTargetData>
{
	enum
	{
		WithNetSerializer = true // This is REQUIRED for FGameplayAbilityTargetDataHandle net serialization to work
	};
};

