// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "TRXInteractionComponent.generated.h"


class ATRXInteracbaleActorBase;
class ATRXPlayerControllerBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ATARAX_API UTRXInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTRXInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool CheckCanInteract(ATRXInteracbaleActorBase* Actor) const;
	void TryInteract() const;
private:
	UFUNCTION(Client, Reliable)
	void TryInteractClient(ATRXInteracbaleActorBase* Actor) const;
	UFUNCTION(Server, Reliable)
	void TryInteractServer(ATRXInteracbaleActorBase* Actor) const;
	UPROPERTY()
	ATRXInteracbaleActorBase* CurrentActiveActor;
	UPROPERTY()
	ATRXPlayerControllerBase* PC;
	UPROPERTY(EditAnywhere)
	int Distance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	bool DebugTrace = false;
};
