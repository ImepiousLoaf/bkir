// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TRXInteractionInterface.h"
#include "GameFramework/Actor.h"
#include "TRXInteracbaleActorBase.generated.h"

UCLASS()
class ATARAX_API ATRXInteracbaleActorBase : public AActor, public ITRXInteractionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATRXInteracbaleActorBase();
	virtual bool CanInteract(AActor* Interactor) const override;
	virtual void InteractClient(AActor* Interactor) override;
	virtual void InteractServer(AActor* Interactor) override;
	virtual void Highlight(bool bEnable) override;

protected:
	virtual UPrimitiveComponent* GetMesh() override;
	virtual UPrimitiveComponent* GetCollider() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
