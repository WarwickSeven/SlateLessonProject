// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManagerComponent.h"

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
		
		InventoryWidget->Init(FMath::Max(MinInventorySize, LocalInventoryComponent->GetItemsNum()));
		InventoryWidget->OnItemDrop.AddUObject(this, &ThisClass::OnItemDropFunc);

		for (const auto& [SlotIndex, SlotInfo] : LocalInventoryComponent->GetItems())
		{
			if (auto* Data = GetItemData(SlotInfo.Id))
			{
				InventoryWidget->AddItem(SlotInfo, *Data, SlotIndex);
			}
		}
	}
}

const FInventoryItemInfo* UInventoryManagerComponent::GetItemData(const FName& InID) const
{
	return ItemsData ? ItemsData->FindRow<FInventoryItemInfo>(InID,"") : nullptr;
}

void UInventoryManagerComponent::OnItemDropFunc(UInventoryCellWidget* From, UInventoryCellWidget* To)
{
	FInventorySlotInfo FromItem = From->GetItem();
	FInventorySlotInfo ToItem = To->GetItem();

	From->Clear();
	To->Clear();

	To->AddItem(FromItem, *GetItemData(FromItem.Id));

	if (!ToItem.Id.IsNone())
	{
		From->AddItem(ToItem, *GetItemData(ToItem.Id));
	}
}
