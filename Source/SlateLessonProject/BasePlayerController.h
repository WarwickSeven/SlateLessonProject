// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

UCLASS(Abstract)
class SLATELESSONPROJECT_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABasePlayerController();

	FSimpleMulticastDelegate OnMouseButtonUp;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	void OnLeftMouseButtonUp();
	
public:
	virtual void Tick(float DeltaSeconds) override;
};
