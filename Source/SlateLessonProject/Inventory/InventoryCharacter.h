// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EquipInterface.h"
#include "InventoryWidget.h"
#include "InventoryCharacter.generated.h"

class UInventoryComponent;
class UInventoryManagerComponent;
class UEquipInventoryComponent;

UCLASS(Abstract)
class SLATELESSONPROJECT_API AInventoryCharacter : public ACharacter, public IEquipInterface
{
	GENERATED_BODY()

public:
	
	AInventoryCharacter();

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UInventoryComponent* LocalInventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UInventoryManagerComponent* InventoryManager;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UEquipInventoryComponent* EquipInventory;

	virtual void EquipItem(EEquipSlot Slot, FName ItemId) override;

	virtual void UnequipItem(EEquipSlot Slot, FName ItemId) override;

	UStaticMeshComponent* GetEquipComponent(EEquipSlot EquipSlot);

	UPROPERTY(BlueprintReadOnly)
	int32 Damage = 0;
};
