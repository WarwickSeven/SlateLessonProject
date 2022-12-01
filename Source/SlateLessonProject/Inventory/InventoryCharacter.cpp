// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryCharacter.h"
#include "InventoryComponent.h"
#include "InventoryManagerComponent.h"


AInventoryCharacter::AInventoryCharacter()
{
	LocalInventory = CreateDefaultSubobject<UInventoryComponent>("LocalInventory");
	InventoryManager = CreateDefaultSubobject<UInventoryManagerComponent>("InventoryManager");
}

void AInventoryCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	InventoryManager->Init(LocalInventory);
}