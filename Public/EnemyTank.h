// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "AIController.h"
#include "Engine/EngineTypes.h"
#include "NavigationSystem.h"
#include "Engine/TargetPoint.h"
#include "EnemyTank.generated.h"

/**
 * 
 */
UCLASS()
class ULTIMATETANKS_API AEnemyTank : public ATank
{
	GENERATED_BODY()

private:
	UNavigationSystemV1* navSystem;
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void Fire() override;

	virtual void OnDestroyTank() override;

	UFUNCTION()
	void GetNewDestination();

	UFUNCTION()
	void MoveToDestination();

	virtual void ReadyToFire() override;

	UPROPERTY(EditAnywhere, Category = "AI")
		float StoppingDistance;

	UPROPERTY(EditAnywhere, Category = "AI")
		AActor* player;

	UPROPERTY(EditAnywhere, Category = "AI")
		TArray<ATargetPoint*> Waypoints;

	UPROPERTY(VisibleAnywhere, Category = "AI")
		int currentWaypointIndex = -1;

public:
	AAIController* controller;

	UPROPERTY(EditAnywhere, Category = "AI")
		float maxWaitTime;
};
