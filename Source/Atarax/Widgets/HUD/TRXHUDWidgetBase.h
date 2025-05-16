// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TRXHUDWidgetBase.generated.h"

class UCanvasPanel;
/**
 * 
 */
UCLASS()
class ATARAX_API UTRXHUDWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	UCanvasPanel* GetCanvas() const;
	
private:
	UPROPERTY(BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess=true, BindWidget))
	UCanvasPanel* Canvas;


};