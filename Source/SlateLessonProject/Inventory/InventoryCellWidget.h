// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryData.h"
#include "Blueprint/UserWidget.h"
#include "InventoryCellWidget.generated.h"

class UInventoryComponent;
class UImage;
class UTextBlock;
class UInventoryWidget;

UCLASS(Abstract)
class SLATELESSONPROJECT_API UInventoryCellWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE bool HasItem() const { return bHasItem; }

	bool AddItem(const FInventorySlotInfo& InSlot, const FInventoryItemInfo& Info);

	void Clear();

	FORCEINLINE const FInventorySlotInfo& GetItem() const { return Item; }

	UPROPERTY(EditAnywhere)
	int32 IndexInInventory = INDEX_NONE;

	FOnItemDrop OnItemDrop;

	UPROPERTY()
	UInventoryWidget* ParentInventoryWidget;

	UInventoryComponent* GetParentInventory() const;
	
protected:

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
	UPROPERTY(EditAnywhere)
	bool bCanDrag = true;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* ItemImage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* CountText;

	bool bHasItem;

	UPROPERTY()
	FInventorySlotInfo Item;
};
