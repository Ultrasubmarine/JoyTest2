// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JoyTestGameMode.generated.h"

UCLASS(minimalapi)
class AJoyTestGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AJoyTestGameMode();

	void PlayerDied(AController* p);

};



