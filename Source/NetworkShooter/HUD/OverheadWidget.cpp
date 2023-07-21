// Fill out your copyright notice in the Description page of Project Settings.


#include "OverheadWidget.h"

#include "Components/TextBlock.h"

void UOverheadWidget::SetDisplayText(FString TextToDisplay) const
{
	if (DisplayText)
	{
		DisplayText->SetText(FText::FromString(TextToDisplay));
	}
}

void UOverheadWidget::ShowPlayerNetRole(APawn* InPawn)
{
	if (!InPawn)
	{
		return;
	}
	
	ENetRole LocalRole = InPawn->GetLocalRole();
	FString Role;

	switch (LocalRole)
	{
	case ROLE_None:
		Role = "ROLE_None";
		break;
	case ROLE_SimulatedProxy:
		Role = "ROLE_SimulatedProxy";
		break;
	case ROLE_AutonomousProxy:
		Role = "ROLE_AutonomousProxy";
		break;
	case ROLE_Authority:
		Role = "ROLE_Authority";
		break;
	case ROLE_MAX:
		Role = "ROLE_MAX";
		break;
	}

	FString LocalRoleString = FString::Printf(TEXT("local Role: %s"), *Role);
	SetDisplayText(LocalRoleString);
}

void UOverheadWidget::NativeDestruct()
{
	Super::NativeDestruct();

	RemoveFromParent();
}
