// Fill out your copyright notice in the Description page of Project Settings.


#include "TRXPlayerMainCharacter.h"


// Sets default values
ATRXPlayerMainCharacter::ATRXPlayerMainCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//WeaponSkeletonMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponSkeletonMesh");
}

// Called when the game starts or when spawned
void ATRXPlayerMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATRXPlayerMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATRXPlayerMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
