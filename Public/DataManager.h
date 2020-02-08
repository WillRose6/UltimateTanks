// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DataManager.generated.h"

/**
 * 
 */
UCLASS()
class ULTIMATETANKS_API UDataManager : public UGameInstance
{
	GENERATED_BODY()

private:
	UDataManager();

public:
	int levelNum;
};
