// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Menu.generated.h"


class UButton;

/**
 * 
 */
UCLASS()
class NETWORKSHOOTER_API UMenu : public UUserWidget
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable)
	void MenuSetup();

private:

	UPROPERTY(meta = (BindWidget))
	UButton * HostButton;

	UPROPERTY(meta = (BindWidget))
	UButton * JoinButton;

	class UMultiplayerSessionsSubsystem* MultiplayerSessionsSubsystem;

	UFUNCTION()
	void HostButtonclicked();

	UFUNCTION()
	void JoinButtonclicked();

	void MenuTearDown();

protected:
	virtual bool Initialize() override;
	
	virtual void NativeDestruct() override;

	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);
	
	void OnFindSession(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWassuccessfull);
	
	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);

	UFUNCTION()
	void OnDestroySession(bool bWasSuccessful);

	UFUNCTION()
	void OnStartSession(bool bWasSuccessful);
};
