// Copyright Epic Games, Inc. All Rights Reserved.

#include "SessionHandlingSteamGameMode.h"
#include "SessionHandlingSteamCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASessionHandlingSteamGameMode::ASessionHandlingSteamGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
