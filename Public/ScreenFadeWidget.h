// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextBlock.h"
#include "ScreenFadeWidget.generated.h"

/**
 * 
 */
UCLASS()
class ULTIMATETANKS_API UScreenFadeWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* LevelCompleteText;

public:
	UFUNCTION()
	void setText(FString inText);
};
