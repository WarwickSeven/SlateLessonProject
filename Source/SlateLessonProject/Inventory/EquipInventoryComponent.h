// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "EquipInventoryComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SLATELESSONPROJECT_API UEquipInventoryComponent : public UInventoryComponent
{
	GENERATED_BODY()

public:

	UEquipInventoryComponent();

	//увязка индекса слота с типом слота
	UPROPERTY(EditAnywhere)
	TMap<int32, EEquipSlot> EquipSlots;

	//проверка соответствия слота и вещи (я бы сделал булевую)
	virtual int32 GetMaxItemAmount(int32 SlotIndex, const FInventoryItemInfo& InItem) override;

	virtual void SetItem(int32 SlotIndex, const FInventorySlotInfo& Item) override;

	virtual void ClearItem(int32 SlotIndex) override;
};
