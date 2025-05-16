// Fill out your copyright notice in the Description page of Project Settings.


#include "TRXUIController.h"

#include "Blueprint/UserWidget.h"


// Sets default values for this component's properties
UTRXUIController::UTRXUIController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTRXUIController::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UTRXUIController::ToggleWidget(UUserWidget* Widget)
{
	if (Widget)
	{
		if (CurrentWidget && CurrentWidget->GetClass() == Widget->GetClass())
		{
			HideWidget();
		}
		else
		{
			SetWidget(Widget);
		}
	}
}

void UTRXUIController::HideWidget()
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;
	}
}

void UTRXUIController::ShowWidget(UUserWidget* Widget)
{
	if (CurrentWidget)
	{
		HideWidget();
	}
	if (Widget)
	{
		CurrentWidget = Widget;
		CurrentWidget->AddToViewport();
	}
}

void UTRXUIController::SetWidget(UUserWidget* Widget)
{
	if (Widget)
	{
		if (CurrentWidget)
		{
			HideWidget();
		}
		ShowWidget(Widget);
	}
}


// Called every frame
void UTRXUIController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
