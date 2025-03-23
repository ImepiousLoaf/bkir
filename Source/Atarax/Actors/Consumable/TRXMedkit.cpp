// Fill out your copyright notice in the Description page of Project Settings.


#include "TRXMedkit.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

// Sets default values
ATRXMedkit::ATRXMedkit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATRXMedkit::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ATRXMedkit::ApplyEffectToTarget(AActor* Target)
{
	UAbilitySystemComponent* abilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Target);
	if (abilitySystem)
	{
		FGameplayEffectContextHandle contextHandle = abilitySystem->MakeEffectContext();
		contextHandle.AddInstigator(this, this);
		FGameplayEffectSpecHandle specHandle = abilitySystem->MakeOutgoingSpec(EffectClass, 1.f, contextHandle);
		abilitySystem->ApplyGameplayEffectSpecToSelf(*specHandle.Data.Get());
		return true;
	}
	return false;
}

// Called every frame
void ATRXMedkit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

