// Fill out your copyright notice in the Description page of Project Settings.


#include "TRXInventoryGridWidgetBase.h"

#include "Atarax/Common/Helpers/TRXHelpers.h"
#include "Atarax/InventorySysem/TRXInventoryObject.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Object/TRXInventoryObjectDragDropBase.h"

void UTRXInventoryGridWidgetBase::init(UCanvasPanel* CanvasSetup)
{
	Canvas = CanvasSetup;
}

bool UTRXInventoryGridWidgetBase::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (UTRXInventoryObjectDragDropBase* DDOp = Cast<UTRXInventoryObjectDragDropBase>(InOperation))
	{
		IsDragOver = true;
		if (UTRXInventoryObject* Object = DDOp->GetInventoryObject())
		{
			FVector2d MousePos = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());
			FVector2d CanvasPos = Canvas->GetParent()->GetCachedGeometry().GetLocalPositionAtCoordinates(FVector2d(0,0));

			FVector2d LocalCoordinate = MousePos - CanvasPos;

			DragOverLocationAndSize.X = LocalCoordinate.X;
			DragOverLocationAndSize.Y = LocalCoordinate.Y;
			DragOverLocationAndSize.Z = !Object->Rotated ? Object->Width : Object->Height;
			DragOverLocationAndSize.W = !Object->Rotated ? Object->Height : Object->Width;

			UTRXHelpers::PrintString(GetWorld(), DragOverLocationAndSize.ToString(), 2.0f, FColor::Orange, 4);
		}
	}
	
	return Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);
	
}

void UTRXInventoryGridWidgetBase::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
	IsDragOver = false;
}

bool UTRXInventoryGridWidgetBase::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	IsDragOver = false;
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UTRXInventoryGridWidgetBase::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	IsDragOver = false;
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);
}

int32 UTRXInventoryGridWidgetBase::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	if (IsDragOver)
	{
		FPaintContext Context(AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

		FVector2d Size = FVector2d(DragOverLocationAndSize.Z, DragOverLocationAndSize.W);
		FVector2d Center = (FVector2d(DragOverLocationAndSize.X, DragOverLocationAndSize.Y) / 64).RoundToVector() * 64;
		Center.Y += 50;
		Center.X -= Size.X * 32;
		Center.Y -= Size.Y * 32;

		UWidgetBlueprintLibrary::DrawLine(Context, Center, Center + FVector2d(Size.X * 64,0), FLinearColor::Red);
		Center.Y += Size.Y * 64;
		UWidgetBlueprintLibrary::DrawLine(Context, Center, Center + FVector2d(Size.X * 64,0), FLinearColor::Red);
		UWidgetBlueprintLibrary::DrawLine(Context, Center, Center - FVector2d(0,Size.Y * 64), FLinearColor::Red);
		Center.X += Size.X * 64;
		UWidgetBlueprintLibrary::DrawLine(Context, Center, Center - FVector2d(0,Size.Y * 64), FLinearColor::Red);
	}
	return Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
}

UTRXInventoryComponent* UTRXInventoryGridWidgetBase::GetInventoryComponent() const
{
	return InventoryComponent;
}

void UTRXInventoryGridWidgetBase::SetInventoryComponent(UTRXInventoryComponent* const InInventoryComponent)
{
	this->InventoryComponent = InInventoryComponent;
}
