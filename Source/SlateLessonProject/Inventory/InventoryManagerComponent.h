// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "InventoryData.h"
#include "InventoryCellWidget.h"
#include "EquipInventoryComponent.h"
#include "Components/ActorComponent.h"
#include "InventoryManagerComponent.generated.h"

class UInventoryComponent;
class UInventoryWidget;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SLATELESSONPROJECT_API UInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UInventoryManagerComponent();

	void Init(UInventoryComponent* InInventoryComponent);

	void InitEquip(UEquipInventoryComponent* InInventoryComponent); //проверить

	const FInventoryItemInfo* GetItemData(const FName& InID) const;
	
protected:
	
	UPROPERTY()
	UInventoryComponent* LocalInventoryComponent;

	UPROPERTY(EditAnywhere)
	UDataTable* ItemsData;
	
	UPROPERTY(EditAnywhere)
	int32 MinInventorySize = 20;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;
	
	UPROPERTY()
	UInventoryWidget* InventoryWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventoryWidget> EquipWidgetClass;

	UPROPERTY()
	UInventoryWidget* EquipWidget;

	void OnItemDropFunc(UInventoryCellWidget* From, UInventoryCellWidget* To);
};
