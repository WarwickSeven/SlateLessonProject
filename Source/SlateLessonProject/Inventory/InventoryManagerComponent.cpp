// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManagerComponent.h"
#include "InventoryCellWidget.h"
#include "InventoryWidget.h"
#include "Blueprint/UserWidget.h"

UInventoryManagerComponent::UInventoryManagerComponent()
{
	//
}

void UInventoryManagerComponent::Init(UInventoryComponent* InInventoryComponent)
{
	if (InInventoryComponent && ItemsData && InventoryWidgetClass)
	{
		LocalInventoryComponent = InInventoryComponent;
		LocalInventoryComponent->CurrentInit(ItemsData); //инициализация Items
		
		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
		InventoryWidget->AddToViewport();
		InventoryWidget->ParentInventory = InInventoryComponent;
		
		InventoryWidget->Init(FMath::Max(MinInventorySize, LocalInventoryComponent->GetItemsNum()));
		InventoryWidget->OnItemDrop.AddUObject(this, &ThisClass::OnItemDropFunc);
		
		for (const auto& Item : LocalInventoryComponent->GetItems())
		{
			if (auto* Data = GetItemData(Item.Value.Id))
			{
				InventoryWidget->AddItem(Item.Value, *Data, Item.Key);
			}
		}
	}
}

void UInventoryManagerComponent::InitEquip(UEquipInventoryComponent* InInventoryComponent)
{
	if (InInventoryComponent && EquipWidgetClass)
	{
		EquipWidget = CreateWidget<UInventoryWidget>(GetWorld(), EquipWidgetClass);
		EquipWidget->ParentInventory = InInventoryComponent;
		EquipWidget->OnItemDrop.AddUObject(this, &ThisClass::OnItemDropFunc);
		EquipWidget->AddToViewport();
	}
}

const FInventoryItemInfo* UInventoryManagerComponent::GetItemData(const FName& InID) const
{
	return ItemsData ? ItemsData->FindRow<FInventoryItemInfo>(InID,"") : nullptr;
}

void UInventoryManagerComponent::OnItemDropFunc(UInventoryCellWidget* From, UInventoryCellWidget* To)
{
	if (From == nullptr || To == nullptr)
	{
		return;
	}
	
	auto* FromInventory = From->GetParentInventory();
	auto* ToInventory = To->GetParentInventory();

	if (FromInventory == nullptr || ToInventory == nullptr)
	{
		return;
	}

	const FInventorySlotInfo FromItem = From->GetItem();
	if (FromItem.Count == 0) //если в исходной ячейке нет предмета 
	{
		return;
	}

	const FInventorySlotInfo ToItem = To->GetItem(); //кешируем предмет из конечной ячейки
	const FInventoryItemInfo* FromInfo = GetItemData(FromItem.Id); //информация о предмете из начальной ячейки

	const int32 ToItemAmount = ToInventory->GetMaxItemAmount(To->IndexInInventory, *FromInfo);
	if (ToItemAmount == 0) //можем ли поместить предмет в инвентарь
	{
		return;
	}

	//кешируем нач. и кон. ячейки и меняем их местами
	FInventorySlotInfo NewFromItem = ToItem;
	FInventorySlotInfo NewToItem = FromItem;

	if (ToItemAmount > 0 && ToItemAmount < FromItem.Count)
	{
		NewToItem.Count = ToItemAmount;
		NewFromItem.Id = NewToItem.Id;
		NewFromItem.Count = FromItem.Count - NewToItem.Count;
	}

	const FInventoryItemInfo* NewFromInfo = NewFromItem.Count > 0 ? GetItemData(NewFromItem.Id) : nullptr;
	const FInventoryItemInfo* NewToInfo = GetItemData(NewToItem.Id);

	From->Clear();
	if (NewFromInfo)
	{
		From->AddItem(NewFromItem, *NewFromInfo);
	}

	To->Clear();
	if (NewToInfo)
	{
		To->AddItem(NewToItem, *NewToInfo);
	}
	
	FromInventory->SetItem(From->IndexInInventory, NewFromItem);
	ToInventory->SetItem(To->IndexInInventory, NewToItem);
	
	/*
	FInventorySlotInfo FromItem = From->GetItem();
	FInventorySlotInfo ToItem = To->GetItem();

	From->Clear();
	To->Clear();

	To->AddItem(FromItem, *GetItemData(FromItem.Id));

	if (!ToItem.Id.IsNone())
	{
		From->AddItem(ToItem, *GetItemData(ToItem.Id));
	}
	*/
}
