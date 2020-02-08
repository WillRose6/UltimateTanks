// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyTank.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerTank.h"
#include "UltimateTanksGameModeBase.h"

void AEnemyTank::BeginPlay() {
	Super::BeginPlay();

	currentWaypointIndex = -1;
	Cast<AUltimateTanksGameModeBase>(GetWorld()->GetAuthGameMode())->ChangeEnemiesAlive(1);

	if (!player) {
		player = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerTank::StaticClass());
	}

	controller = Cast<AAIController>(GetController());
	navSystem = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());
	GetNewDestination();
}

void AEnemyTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector dir = Waypoints[currentWaypointIndex]->GetActorLocation() - GetActorLocation();
	FRotator toDestination = FRotator(0, dir.Rotation().Yaw, 0);
	MainMesh->SetWorldRotation(FMath::RInterpTo(MainMesh->GetComponentRotation(), toDestination, DeltaTime, 10.0f));

	if(player){
		FVector toPlayer = GetActorLocation() - player->GetActorLocation();
		FRotator rot = FRotator(0, toPlayer.Rotation().Yaw, 0);
		CannonMesh->SetRelativeRotation(rot);
	}

	ATargetPoint* point = Waypoints[currentWaypointIndex];
	float distance = FVector::Distance(GetActorLocation(), FVector(point->GetActorLocation().X, point->GetActorLocation().Y, GetActorLocation().Z));
	if (distance <= StoppingDistance) {
		GetNewDestination();
	}
}

void AEnemyTank::ReadyToFire() {
	Super::ReadyToFire();
	FHitResult hit;
	FCollisionQueryParams CollisionParameters;
	FVector startLocation = firePoint->GetComponentLocation();
	FVector endLocation = startLocation + (firePoint->GetForwardVector() * 500.0f);
	GetWorld()->LineTraceSingleByChannel(hit, startLocation, endLocation, ECollisionChannel::ECC_WorldDynamic, CollisionParameters);

	if(hit.Actor == NULL){
		Fire();
	}
	else {
		ResetFire();
	}
}

void AEnemyTank::GetNewDestination() {
	if(currentWaypointIndex != Waypoints.Num()-1){
		currentWaypointIndex++;
	}
	else {
		currentWaypointIndex = 0;
	}

	FTimerHandle* handle = new FTimerHandle;
	GetWorldTimerManager().SetTimer(*handle, this, &AEnemyTank::MoveToDestination, FMath::RandRange(0.0f, maxWaitTime), false);
}

void AEnemyTank::MoveToDestination()
{
	ATargetPoint* point = Waypoints[currentWaypointIndex];

	if (point) {
		controller->MoveToLocation(point->GetActorLocation(), -1.0f);
	}
}

void AEnemyTank::Fire() {
	Super::Fire();
}

void AEnemyTank::OnDestroyTank()
{
	Super::OnDestroyTank();
	Cast<AUltimateTanksGameModeBase>(GetWorld()->GetAuthGameMode())->ChangeEnemiesAlive(-1);
}

