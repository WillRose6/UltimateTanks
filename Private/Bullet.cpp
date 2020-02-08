// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "..\Public\Bullet.h"
#include "Components/PrimitiveComponent.h"
#include "PlayerTank.h"
#include "ExplodableComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComponent;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	explosionComponent = CreateDefaultSubobject<UExplodableComponent>(TEXT("Explosion component"));
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	MeshComponent->OnComponentHit.AddDynamic(this, &ABullet::OnComponentHit);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector vel = GetVelocity();
	vel = FVector(vel.X, vel.Y, 0);
	FRotator rot = FMath::RInterpTo(GetActorRotation(), vel.Rotation(), DeltaTime, 30.0f);
	SetActorRotation(rot);
}

void ABullet::OnComponentHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & hit)
{
	UExplodableComponent* otherExplodeComp = OtherActor->FindComponentByClass<UExplodableComponent>();

	if(otherExplodeComp){
		otherExplodeComp->Explode();

		if (explosionComponent) {
			explosionComponent->Explode();
		}
	}

	if(numberOfBounces < maxBounces) {
		Bounce(hit);
		return;
	}

	if (explosionComponent) {
		explosionComponent->Explode();
	}
}

void ABullet::Bounce(FHitResult hit)
{
	MeshComponent->AddImpulse(hit.Normal * bounceImpulse);
	numberOfBounces++;
}

