// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TRXInventoryObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ATARAX_API UTRXInventoryObject : public UObject
{
	GENERATED_BODY()
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual bool IsSupportedForNetworking() const override { return true; }
	UFUNCTION()
	void hut();
public:
	UPROPERTY(ReplicatedUsing=hut, BlueprintReadWrite)
	int Prepon = 4;
};
