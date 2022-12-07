// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryData.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

UCLASS(ClassGroup=("Inventory"), meta=(BlueprintSpawnableComponent))
class SLATELESSONPROJECT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	FORCEINLINE const FInventorySlotInfo* GetItem(int32 SlotIndex) const { return Items.Find(SlotIndex); }

	//UFUNCTION()
	virtual void SetItem(int32 SlotIndex, const FInventorySlotInfo& Item);

	virtual void ClearItem(int32 SlotIndex);

	//сколько предметов можем поместить в ячейку (0- не можем; 1- 1;-1- бесконечно)
	virtual int32 GetMaxItemAmount(int32 SlotIndex, const FInventoryItemInfo& InItem);

	FORCEINLINE const TMap<int32, FInventorySlotInfo>& GetItems() const { return Items; }

	FORCEINLINE int32 GetItemsNum() const { return Items.Num(); }

	virtual void CurrentInit(const UDataTable* ItemsData);
	
protected:
	
	UPROPERTY()
	TMap<int32, FInventorySlotInfo> Items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* CurrentItemsTable;
};
