// Copyright Epic Games, Inc. All Rights Reserved.

#include "SlateLessonProjectGameMode.h"
#include "SlateLessonProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASlateLessonProjectGameMode::ASlateLessonProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
