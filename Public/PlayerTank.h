// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "PlayerTank.generated.h"

/**
 * 
 */
UCLASS()
class ULTIMATETANKS_API APlayerTank : public ATank
{
	GENERATED_BODY()

protected:
		virtual void BeginPlay() override;

		virtual void MoveForward(float Value) override;

		virtual void MoveRight(float Value) override;

		APlayerController* PlayerController;

		virtual void ReadyToFire() override;

		virtual void OnDestroyTank() override;

public:
	APlayerTank();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
