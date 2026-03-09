// Copyright Epic Games, Inc. All Rights Reserved.

#include "HandProjectGameMode.h"
#include "HandProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHandProjectGameMode::AHandProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
