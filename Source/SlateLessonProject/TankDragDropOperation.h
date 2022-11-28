// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DraggableItem.h"
#include "Blueprint/DragDropOperation.h"
#include "TankDragDropOperation.generated.h"

UCLASS()
class SLATELESSONPROJECT_API UTankDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	
	UPROPERTY()
	UDraggableItem* OriginWidget;
};
