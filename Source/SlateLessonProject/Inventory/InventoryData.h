#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "InventoryData.generated.h"


UENUM()
enum class EItemType : uint8
{
	It_Misc,
	It_Currency,
	It_Equip,
	It_Consumable,	
};

UENUM()
enum class EItemRarity : uint8
{
	Ir_Common,
	Ir_Rare,
	Ir_Epic,
};

UENUM()
enum class EEquipSlot : uint8
{
	Es_Head,
	Es_LeftArm,
	Es_Body,
	Es_RightArm,
	Es_LeftLeg,
	Es_RightLeg,
};

class UInventoryCellWidget;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemDrop, UInventoryCellWidget* /*from*/, UInventoryCellWidget* /*to*/)

USTRUCT(BlueprintType)
struct FInventoryItemInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "General")
	FName Id;

	UPROPERTY(EditDefaultsOnly, Category = "General")
	FText Name;

	UPROPERTY(EditDefaultsOnly, Category = "Type")
	EItemType Type;

	UPROPERTY(EditDefaultsOnly, Category = "Type")
	EItemRarity Rare;

	UPROPERTY(EditDefaultsOnly, Category = "Type")
	EEquipSlot EquipSlot;

	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	TSoftObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	int32 Damage;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	int32 Armor;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	int32 Intelligence;
};

USTRUCT(BlueprintType)
struct FInventorySlotInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName Id = NAME_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Count;
};