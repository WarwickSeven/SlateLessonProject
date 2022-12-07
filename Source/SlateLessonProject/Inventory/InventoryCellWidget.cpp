// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryCellWidget.h"
#include "InventoryWidget.h"
// #include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

bool UInventoryCellWidget::AddItem(const FInventorySlotInfo& InSlot, const FInventoryItemInfo& Info)
{
	if (bHasItem)
	{
		return false;
	}

	if (ItemImage)
	{
		ItemImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		ItemImage->SetBrushFromTexture(Info.Icon.LoadSynchronous());
	}

	if (CountText)
	{
		CountText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		CountText->SetText(FText::FromString(FString::FromInt(InSlot.Count)));
	}

	bHasItem = true;
	Item = InSlot;
	
	return true;
}

void UInventoryCellWidget::Clear()
{
	if (!bHasItem)
	{
		return;
	}

	if (ItemImage)
	{
		ItemImage->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (CountText)
	{
		CountText->SetVisibility(ESlateVisibility::Collapsed);
	}

	bHasItem = false;
	Item = {};
}

UInventoryComponent* UInventoryCellWidget::GetParentInventory() const
{
	return ParentInventoryWidget ? ParentInventoryWidget->ParentInventory : nullptr;
}

FReply UInventoryCellWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (bCanDrag && bHasItem && InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}
	//return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	return FReply::Handled();
}

void UInventoryCellWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass());
	if (OutOperation)
	{
		//преподаватель велел в идеале так не делать, а создать отдельный виджет
		OutOperation->DefaultDragVisual = this;
	}
	else
	{
		Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);	
	}
}

bool UInventoryCellWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (InOperation && InOperation->DefaultDragVisual && InOperation->DefaultDragVisual != this)
	{
		if (auto* FromCell = Cast<UInventoryCellWidget>(InOperation->DefaultDragVisual))
		{
			OnItemDrop.Broadcast(FromCell, this);
			return true;
		}
	}
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}
