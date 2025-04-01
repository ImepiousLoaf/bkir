#include "TRXCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "Atarax/AbilitySystem/Components/TRXAbilitySystemComponent.h"
#include "Atarax/GMPSC/PlayerState/TRXPlayerState.h"
#include "Atarax/Characters/Components/Movement/TRXCharacterMovementComponent.h"
#include "Atarax/InventorySysem/TRXInventoryObject.h"
#include "Engine/ActorChannel.h"
#include "Net/UnrealNetwork.h"

void ATRXCharacterBase::debugPrint()
{
	FString str;
	str.AppendInt(oBJiN.Num());
	str.Append(" - ");
	for(const auto& it : oBJiN)
	{
		if(it)
		{
			str.AppendInt(it->Prepon);
		} else
		{
			str.AppendInt(-1);
		}
		str.Append(" ");
	}
	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Magenta, str);
}

void ATRXCharacterBase::gui()
{
		// FString str("prepon replicated: ");
		// str.AppendInt(old ? old->Prepon : -1);
		GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Orange, "ObJin Replicated");
}

void ATRXCharacterBase::MakeObjectToRep(int a)
{
	UTRXInventoryObject* Item = NewObject<UTRXInventoryObject>();
	AddReplicatedSubObject(Item);
	oBJiN.Add(Item);
	oBJiN.Last()->Prepon = a;
}

bool ATRXCharacterBase::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool bWroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);
		
	// Single Object
	//bWroteSomething |= Channel->ReplicateSubobjectList(oBJiN, *Bunch, *RepFlags);
	return bWroteSomething;
}

ATRXCharacterBase::ATRXCharacterBase(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<UTRXCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	YawDelta = 0;
	PrimaryActorTick.bCanEverTick = true;
}

ATRXCharacterBase::ATRXCharacterBase()
{
	bReplicateUsingRegisteredSubObjectList = true;
}

UAbilitySystemComponent* ATRXCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ATRXCharacterBase::InitAbilitySystem()
{
	if (ATRXPlayerState* playerState = GetPlayerState<ATRXPlayerState>())
	{
		if (UTRXAbilitySystemComponent* abilitySystemComponent = Cast<UTRXAbilitySystemComponent>(playerState->GetAbilitySystemComponent()))
		{
			AbilitySystemComponent = abilitySystemComponent;
			AbilitySystemComponent->InitAbilityActorInfo(playerState, this);
		}
	}
}

void ATRXCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilitySystem();
}

void ATRXCharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilitySystem();
}

void ATRXCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ThisClass, oBJiN);
	DOREPLIFETIME_CONDITION(ThisClass, YawDelta, COND_SkipOwner);
}

float ATRXCharacterBase::GetYawDelta() const
{
	return YawDelta;
}

void ATRXCharacterBase::SetYawDelta(float NewYawDelta)
{
	this->YawDelta = NewYawDelta;
}

void ATRXCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		MakeObjectToRep(50);
		MakeObjectToRep(50);
		MakeObjectToRep(50);
	}
}
