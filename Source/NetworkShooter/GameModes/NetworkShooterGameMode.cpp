// Copyright Epic Games, Inc. All Rights Reserved.

#include "NetworkShooterGameMode.h"
#include "NetworkShooter/NetworkShooterCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANetworkShooterGameMode::ANetworkShooterGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
