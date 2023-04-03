// Copyright Epic Games, Inc. All Rights Reserved.

#include "JoyTestGameMode.h"
#include "JoyTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AJoyTestGameMode::AJoyTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AJoyTestGameMode::PlayerDied(AController* p)
{
	RestartPlayer(p);
}
