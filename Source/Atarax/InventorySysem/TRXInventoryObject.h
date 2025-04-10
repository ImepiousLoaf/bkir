// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TRXInventoryObject.generated.h"

/**
 * 
 */

class UWorld;

UCLASS(Blueprintable)
class ATARAX_API UTRXInventoryObject : public UObject
{
	GENERATED_BODY()
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual bool IsSupportedForNetworking() const override { return true; }
	virtual UWorld* GetWorld() const override;
	UFUNCTION()
	void hut();
public:
	UPROPERTY(ReplicatedUsing=hut, BlueprintReadWrite)
	int Prepon = 4;
public:
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess), BlueprintReadOnly)
	UTexture2D* Texture;
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess), BlueprintReadOnly)
	int Width;
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess), BlueprintReadOnly)
	int Height;
	UPROPERTY(Replicated, BlueprintReadWrite, meta=(AllowPrivateAccess))
	int CoordX;
	UPROPERTY(Replicated, BlueprintReadWrite, meta=(AllowPrivateAccess))
	int CoordY;
	UPROPERTY(Replicated, BlueprintReadOnly, meta=(AllowPrivateAccess))
	int Quantity;
	UPROPERTY(Replicated, BlueprintReadOnly, meta=(AllowPrivateAccess))
	bool Rotated;
};

UCLASS(Blueprintable)
class UTRXPipa : public UTRXInventoryObject
{
	GENERATED_BODY()

public:
	
};
