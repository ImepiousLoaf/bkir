// Fill out your copyright notice in the Description page of Project Settings.


#include "TRXInteractionComponent.h"
#include "Atarax/GMPSC/PlayerController/TRXPlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"
#include "TRXInteracbaleActorBase.h"

// Sets default values for this component's properties
UTRXInteractionComponent::UTRXInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTRXInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	PC = Cast<ATRXPlayerControllerBase>(GetOwner());
}


// Called every frame
void UTRXInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (Cast<APlayerController>(GetOwner())->IsLocalController())
	{
		FHitResult HitResult;
		const auto Cam = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
		const FVector Fwd = Cam->GetActorForwardVector();
		const FVector Loc = Cam->GetCameraLocation();
		Distance = 1000000;
		const FVector End = Loc + Fwd * Distance;

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(PC->GetPawn());

		GetWorld()->LineTraceSingleByChannel(HitResult, Loc, End, ECollisionChannel::ECC_Visibility, Params);

		auto HitActor = HitResult.GetActor();

		if (DebugTrace)
		{
			DrawDebugSphere(GetWorld(), HitResult.Location, 50, 50, FColor::Red, false);
		}

		if (HitActor && HitActor->Implements<UTRXInteractionInterface>())
		{
			if (ATRXInteracbaleActorBase* ActiveActor = Cast<ATRXInteracbaleActorBase>(HitActor); ActiveActor != CurrentActiveActor)
			{
				CurrentActiveActor->Highlight(false);
				CurrentActiveActor = ActiveActor;
				CurrentActiveActor->Highlight(true);
			}
		}
		else
		{
			if (CurrentActiveActor)
				CurrentActiveActor->Highlight(false);
			CurrentActiveActor = nullptr;
		}
	}
	else
	{
		PrimaryComponentTick.bCanEverTick = false;
	}
}

bool UTRXInteractionComponent::CheckCanInteract(ATRXInteracbaleActorBase* Actor) const
{
	if (CurrentActiveActor)
		return CurrentActiveActor->CanInteract(GetOwner());
	return false;
}

void UTRXInteractionComponent::TryInteractClient_Implementation(ATRXInteracbaleActorBase* Actor) const
{
	if (CurrentActiveActor)
		CurrentActiveActor->InteractClient(GetOwner());
}

void UTRXInteractionComponent::TryInteractServer_Implementation(ATRXInteracbaleActorBase* Actor) const
{
	if (Actor)
	{
		if (Actor->CanInteract(GetOwner()))
		{
			Actor->InteractServer(GetOwner());
			TryInteractClient(Actor);
		}
	}
}

void UTRXInteractionComponent::TryInteract() const
{
	if (CurrentActiveActor)
	{
		TryInteractServer(CurrentActiveActor);
	}
}
