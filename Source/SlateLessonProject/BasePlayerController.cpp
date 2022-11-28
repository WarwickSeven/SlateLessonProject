// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"

ABasePlayerController::ABasePlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	bEnableClickEvents = true;
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputComponent)
	{
		InputComponent->BindKey(EKeys::LeftMouseButton, IE_Released, this, &ThisClass::OnLeftMouseButtonUp);
	}
}

void ABasePlayerController::OnLeftMouseButtonUp()
{
	OnMouseButtonUp.Broadcast();
}

void ABasePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}


