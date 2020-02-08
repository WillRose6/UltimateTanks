// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplodableComponent.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UExplodableComponent::UExplodableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UExplodableComponent::Explode()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionSystem, GetOwner()->GetActorLocation());
	ATank* tank = Cast<ATank>(GetOwner());
	if (tank) {
		tank->OnDestroyTank();
	}
	GetWorld()->DestroyActor(GetOwner());
}

