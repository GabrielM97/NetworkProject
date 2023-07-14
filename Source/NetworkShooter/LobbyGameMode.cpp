// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (GameState)
	{
		int32 NumberOfPlayer = GameState.Get()->PlayerArray.Num();
		
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				1,
				60.f,
				FColor::Green,
				FString::Printf(TEXT("Players in game: %d"), NumberOfPlayer));

			if (APlayerState* PlayerState = NewPlayer->GetPlayerState<APlayerState>())
			{
				FString PlayerName = PlayerState->GetPlayerName();

				GEngine->AddOnScreenDebugMessage(
				-1,
				60.f,
				FColor::Yellow,
				FString::Printf(TEXT("%s Has joined the game"), *PlayerName));
			}
			
		}
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	
	
	if (GameState)
	{
		int32 NumberOfPlayer = GameState.Get()->PlayerArray.Num();
		
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				1,
				60.f,
				FColor::Green,
				FString::Printf(TEXT("Players in game: %d"), NumberOfPlayer - 1));

			if (APlayerState* PlayerState = Exiting->GetPlayerState<APlayerState>())
			{
				FString PlayerName = PlayerState->GetPlayerName();

				GEngine->AddOnScreenDebugMessage(
				-1,
				60.f,
				FColor::Yellow,
				FString::Printf(TEXT("%s Has left the game"), *PlayerName));
			}
			
		}
	}
			
}
