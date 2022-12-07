// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryCharacter.h"
#include "EquipInventoryComponent.h"
#include "InventoryComponent.h"
#include "InventoryManagerComponent.h"


AInventoryCharacter::AInventoryCharacter()
{
	LocalInventory = CreateDefaultSubobject<UInventoryComponent>("LocalInventory");
	EquipInventory = CreateDefaultSubobject<UEquipInventoryComponent>("EquipInventory");
	InventoryManager = CreateDefaultSubobject<UInventoryManagerComponent>("InventoryManager");
}

void AInventoryCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	InventoryManager->Init(LocalInventory);
	InventoryManager->InitEquip(EquipInventory);
}

void AInventoryCharacter::EquipItem(EEquipSlot Slot, FName ItemId)
{
	if (UStaticMeshComponent* Comp = GetEquipComponent(Slot))
	{
		if (auto* Info = InventoryManager->GetItemData(ItemId))
		{
			Comp->SetStaticMesh(Info->Mesh.LoadSynchronous());
			Comp->SetHiddenInGame(false);

			Damage += Info->Damage;
		}
	}
}

void AInventoryCharacter::UnequipItem(EEquipSlot Slot, FName ItemId)
{
	if (UStaticMeshComponent* Comp = GetEquipComponent(Slot))
	{
		Comp->SetStaticMesh(nullptr);
		Comp->SetHiddenInGame(true);
		
		if (auto* Info = InventoryManager->GetItemData(ItemId))
		{
			Damage -= Info->Damage;
		}
	}
}

UStaticMeshComponent* AInventoryCharacter::GetEquipComponent(EEquipSlot EquipSlot)
{
	FName Tag;

	switch (EquipSlot)
	{
	case EEquipSlot::Es_Head: Tag = "Head"; break;
	case EEquipSlot::Es_LeftArm: Tag = "LeftArm"; break;
	case EEquipSlot::Es_RightArm: Tag = "RightArm"; break;
	case EEquipSlot::Es_Body: Tag = "Body"; break;
	case EEquipSlot::Es_LeftLeg: Tag= "LeftLeg"; break;
	case EEquipSlot::Es_RightLeg: Tag= "RightLeg"; break;
	default: return nullptr;
	}

	TArray<UActorComponent*> Found = GetComponentsByTag(UStaticMeshComponent::StaticClass(), Tag);

	return Found.Num() > 0 ? StaticCast<UStaticMeshComponent*>(Found[0]) : nullptr;
}
