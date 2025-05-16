// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Atarax/InventorySysem/Components/TRXInventoryComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "TRXInventoryGridWidgetBase.generated.h"

class UTRXInventoryObjectWidgetBase;
class UTRXInventoryComponent;
/**
 * 
 */
UCLASS()
class ATARAX_API UTRXInventoryGridWidgetBase : public UUserWidget
{
	GENERATED_BODY()


public:
	UTRXInventoryComponent* GetInventoryComponent() const;
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetInventoryComponent(UTRXInventoryComponent* const InInventoryComponent);

private:
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void init(UCanvasPanel* CanvasSetup);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void Update();
	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inventory", meta=(AllowPrivateAccess=true))
	int Width;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inventory", meta=(AllowPrivateAccess=true))
	int Height;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inventory", meta=(AllowPrivateAccess=true))
	TSubclassOf<UTRXInventoryObjectWidgetBase> InventoryObjectWidgetCLass;
	UPROPERTY(BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess=true, ExposeOnSpawn=true))
	UTRXInventoryComponent* InventoryComponent;


	UPROPERTY(BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess=true, BindWidget))
	UCanvasPanel* Canvas;
	UPROPERTY(BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess=true))
	bool IsDragOver;

	
	FIntVector4 DragOverLocationAndSize;
	FVector2d GridCoord;
};
