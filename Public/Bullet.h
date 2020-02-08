// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class ULTIMATETANKS_API ABullet : public AActor
{
	GENERATED_BODY()
	
private:
	int numberOfBounces;

public:	
	// Sets default values for this actor's properties
	ABullet();

	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category = "Moving")
	class UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Firing")
	float Speed;

	UPROPERTY(EditAnywhere, Category = "Collision")
	UParticleSystem* explosion;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Bouncing")
	int maxBounces;

	UPROPERTY(EditAnywhere, Category = "Bouncing")
	float bounceImpulse;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& hit);

	UFUNCTION()
	void Bounce(FHitResult hit);

	UPROPERTY(VisibleAnywhere, Category = "Explosion")
	class UExplodableComponent* explosionComponent;
};
