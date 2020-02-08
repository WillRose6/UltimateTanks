// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ActorComponent.h"
#include "Tank.generated.h"

UCLASS()
class ULTIMATETANKS_API ATank : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATank();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tank")
		UStaticMeshComponent* CannonMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tank")
		UStaticMeshComponent* MainMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Firing Bullets")
		TSubclassOf<AActor> Bullet;

	UPROPERTY(EditAnywhere, Category = "Firing Bullets")
		USceneComponent* firePoint;

	UPROPERTY(VisibleAnywhere, Category = "Exploding")
		UActorComponent* explosionComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void MoveForward(float Value);
	virtual void MoveRight(float Value);

	UFUNCTION()
		virtual void Fire();

	UFUNCTION()
		virtual void ResetFire();

	UFUNCTION()
		void RotateTowardsMovementDirection(FVector2D inputs);

	UFUNCTION()
		virtual void ReadyToFire();

	UPROPERTY(EditAnywhere, Category = "Tank")
		float RotateSpeed;

	bool bCanFire;
	UPROPERTY(VisibleAnywhere)
	float fireCountdown;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Firing Bullets")
		float FireRate;

	UFUNCTION()
		virtual void OnDestroyTank();
};
