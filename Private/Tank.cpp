// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "..\Public\Tank.h"
#include "DrawDebugHelpers.h"
#include "ExplodableComponent.h"

// Sets default values
ATank::ATank()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon Mesh"));
	CannonMesh->SetupAttachment(RootComponent);

	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main Mesh"));
	MainMesh->SetupAttachment(RootComponent);

	firePoint = CreateDefaultSubobject<USceneComponent>(TEXT("Fire point"));
	firePoint->SetupAttachment(CannonMesh);

	explosionComponent = CreateDefaultSubobject<UExplodableComponent>(TEXT("Explosion component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	fireCountdown = FireRate;
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (fireCountdown <= 0) {
		if (bCanFire == false) {
			ReadyToFire();
		}
	}
	else {
		fireCountdown -= DeltaTime;
	}
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::MoveForward(float Value)
{

}

void ATank::MoveRight(float Value)
{

}

void ATank::ReadyToFire() {
	bCanFire = true;
}

void ATank::RotateTowardsMovementDirection(FVector2D inputs)
{
	FRotator rot = FRotator(0, 0, 0);

	if (inputs.X > 0 && inputs.Y > 0) {
		rot.Yaw = 45;
	}

	if (inputs.X == 0.0f && inputs.Y > 0) {
		rot.Yaw = 90;
	}

	if (inputs.X < 0.0f && inputs.Y > 0) {
		rot.Yaw = 135;
	}

	if (inputs.X < 0.0f && inputs.Y == 0.0f) {
		rot.Yaw = 180;
	}

	if (inputs.X > 0.0f && inputs.Y < 0.0f) {
		rot.Yaw = 315;
	}

	if (inputs.X < 0.0f && inputs.Y < 0.0f) {
		rot.Yaw = 225;
	}

	if (inputs.X == 0.0f && inputs.Y < 0.0f) {
		rot.Yaw = 270;
	}

	FRotator newRot = FMath::RInterpTo(MainMesh->GetComponentRotation(), rot, GetWorld()->GetDeltaSeconds(), RotateSpeed);
	MainMesh->SetWorldRotation(newRot);
}

void ATank::Fire() {
	if (bCanFire) {
		GetWorld()->SpawnActor<AActor>(Bullet, firePoint->GetComponentLocation(), firePoint->GetComponentRotation(), FActorSpawnParameters());
		ResetFire();
	}
}

void ATank::ResetFire()
{
	fireCountdown = FireRate;
	bCanFire = false;
}

void ATank::OnDestroyTank()
{
}

