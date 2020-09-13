// Fill out your copyright notice in the Description page of Project Settings.

#include "PUBGGameModeBase.h"
#include "MyCharacter.h"
#include "CrossHair.h"

APUBGGameModeBase::APUBGGameModeBase()
{
	DefaultPawnClass = AMyCharacter::StaticClass();
	HUDClass = ACrossHair::StaticClass();
}

void APUBGGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);
}

void APUBGGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

