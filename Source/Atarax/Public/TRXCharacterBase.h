#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "TRXCharacterBase.generated.h"

class UGameplayAbility;
class UTRXAbilitySystemComponent;

UCLASS()
class ATRXCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ATRXCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
private:
	UPROPERTY()
	TObjectPtr<UTRXAbilitySystemComponent> AbilitySystemComponent;
	void InitAbilitySystem();
};