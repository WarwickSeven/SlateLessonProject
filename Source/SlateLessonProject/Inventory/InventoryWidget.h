// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryData.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UInventoryComponent;
class UUniformGridPanel;
class UInventoryCellWidget;

UCLASS(Abstract)
class SLATELESSONPROJECT_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	
	void Init(int32 ItemsCount);

	bool AddItem(const FInventorySlotInfo& InSlot, const FInventoryItemInfo& Info, int32 SlotIndex);

	FOnItemDrop OnItemDrop;

	UPROPERTY()
	UInventoryComponent* ParentInventory;

protected:

	UPROPERTY(EditDefaultsOnly)
	int32 ItemsInRow = 5;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryCellWidget> CellWidgetClass;

	//основная панель ячеек 
	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetOptional))
	UUniformGridPanel* CellsPanel;

	//ячейка для золота
	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetOptional))
	UInventoryCellWidget* GoldCell;

	//массив всех созданных ячеек
	UPROPERTY(BlueprintReadWrite)
	TArray<UInventoryCellWidget*> CellWidgets;

	UInventoryCellWidget* CreateCell();

	void InitCell(UInventoryCellWidget* NewCell);
	
	void OnItemDropFunc(UInventoryCellWidget* From, UInventoryCellWidget* To);
};
