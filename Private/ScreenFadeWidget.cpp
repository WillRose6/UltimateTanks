// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenFadeWidget.h"

void UScreenFadeWidget::setText(FString inText)
{
	LevelCompleteText->SetText(FText::FromString(inText));
}
