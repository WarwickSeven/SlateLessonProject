// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipInventoryComponent.h"

#include "EquipInterface.h"

UEquipInventoryComponent::UEquipInventoryComponent()
{
	EquipSlots.Add(0, EEquipSlot::Es_Head);
	EquipSlots.Add(1, EEquipSlot::Es_LeftArm);
	EquipSlots.Add(2, EEquipSlot::Es_Body);
	EquipSlots.Add(3, EEquipSlot::Es_RightArm);
	EquipSlots.Add(4, EEquipSlot::Es_LeftLeg);
	EquipSlots.Add(5, EEquipSlot::Es_RightLeg);
}

int32 UEquipInventoryComponent::GetMaxItemAmount(int32 SlotIndex, const FInventoryItemInfo& InItem)
{
	EEquipSlot* EquipSlotPtr = EquipSlots.Find(SlotIndex);

	//1 - надеваемость предмета
	//2 - валидность
	//3 - соответствовие типа слоту (шлем-голова) 
	if (InItem.Type == EItemType::It_Equip && EquipSlotPtr && *EquipSlotPtr == InItem.EquipSlot)
	{
		return 1;
	}
	return 0;
}

void UEquipInventoryComponent::SetItem(int32 SlotIndex, const FInventorySlotInfo& Item)
{
	auto* InventoryOwner = GetOwner();
	if (!InventoryOwner->Implements<UEquipInterface>())
	{
		Super::SetItem(SlotIndex, Item);
		return;
	}

	if (IEquipInterface* EquipInterface = Cast<IEquipInterface>(InventoryOwner))
	{
		EEquipSlot EquipSlot = EquipSlots.FindChecked(SlotIndex);
		if (auto* ItemInfo = GetItem(SlotIndex))
		{
			EquipInterface->UnequipItem(EquipSlot, ItemInfo->Id);
		}

		Super::SetItem(SlotIndex, Item);

		EquipInterface->EquipItem(EquipSlot, Item.Id);
	}
}

void UEquipInventoryComponent::ClearItem(int32 SlotIndex)
{
	auto* InventoryOwner = GetOwner();
	if (!InventoryOwner->Implements<UEquipInterface>())
	{
		Super::ClearItem(SlotIndex);
		return;
	}

	if (IEquipInterface* EquipInterface = Cast<IEquipInterface>(InventoryOwner))
	{
		EEquipSlot EquipSlot = EquipSlots.FindChecked(SlotIndex);
		if (auto* ItemInfo = GetItem(SlotIndex))
		{
			EquipInterface->UnequipItem(EquipSlot, ItemInfo->Id);
		}
		Super::ClearItem(SlotIndex);
	}
}
