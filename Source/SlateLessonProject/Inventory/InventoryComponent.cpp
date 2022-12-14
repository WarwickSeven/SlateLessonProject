// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

void UInventoryComponent::SetItem(int32 SlotIndex, const FInventorySlotInfo& Item)
{
	ClearItem(SlotIndex);
	Items.Add(SlotIndex, Item);
}

void UInventoryComponent::ClearItem(int32 SlotIndex)
{
	Items.Remove(SlotIndex);
}

int32 UInventoryComponent::GetMaxItemAmount(int32 SlotIndex, const FInventoryItemInfo& InItem)
{
	// FInventorySlotInfo* SlotPtr = Items.Find(SlotIndex);
	// if (SlotPtr == nullptr || SlotPtr->Id == InItem.Id)
	// {
	// 	return 0;
	// }
	return -1; // бесконечный стэк предметов 
}

void UInventoryComponent::CurrentInit(const UDataTable* ItemsData) //Data - общий DataTable
{
	FString ContextString;
	TArray<FInventorySlotInfo*> OutAllRows;
	CurrentItemsTable->GetAllRows<FInventorySlotInfo>(ContextString, OutAllRows);
	//необходимо добавить сверку с DataTable
	for (int32 i = 0; i < OutAllRows.Num(); i++)
	{
		SetItem(i+1, *OutAllRows[i]);
	}
}

