// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuUI.h"
#include "UltimateTanksGameModeBase.h"

void UMenuUI::NativeConstruct()
{
	Super::NativeConstruct();
	PlayButton->OnClicked.AddDynamic(this, &UMenuUI::PlayGame);
	QuitButton->OnClicked.AddDynamic(this, &UMenuUI::QuitGame);
}

void UMenuUI::PlayGame()
{
	Cast<AUltimateTanksGameModeBase>(GetWorld()->GetAuthGameMode())->LoadNextLevel(0.0f);
}

void UMenuUI::QuitGame()
{
	FGenericPlatformMisc::RequestExit(false);
}
