#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "TRXCharacterBase.generated.h"

class UTRXInventoryObject;
class UTRXCharacterMovementComponent;
class UGameplayAbility;
class UTRXAbilitySystemComponent;

UCLASS()
class ATRXCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(ReplicatedUsing=gui, BlueprintReadWrite)
	TArray<UTRXInventoryObject*> oBJiN;

	UFUNCTION(BlueprintCallable)
	void debugPrint();
	UFUNCTION()
	void gui();
	UFUNCTION(BlueprintCallable)
	void MakeObjectToRep(int a);
	
	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;
	ATRXCharacterBase(const FObjectInitializer& ObjectInitializer);
	ATRXCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UFUNCTION(BlueprintCallable, Category="Movement")
	float GetYawDelta() const;
	void SetYawDelta(float NewYawDelta);

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
private:
	UPROPERTY(Replicated)
	float YawDelta;

	UPROPERTY()
	TObjectPtr<UTRXAbilitySystemComponent> AbilitySystemComponent;
	void InitAbilitySystem();
};