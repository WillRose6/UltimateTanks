// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "MenuUI.generated.h"

/**
 * 
 */
UCLASS()
class ULTIMATETANKS_API UMenuUI : public UUserWidget
{
	GENERATED_BODY()
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void PlayGame();

	UFUNCTION()
	void QuitGame();
	
public:
	UPROPERTY(meta = (BindWidget))
	UButton* PlayButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;
};
