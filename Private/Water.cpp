// Fill out your copyright notice in the Description page of Project Settings.


#include "Water.h"
#include "Tank.h"
#include "ExplodableComponent.h"

// Sets default values
AWater::AWater()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Water mesh"));
	RootComponent = mesh;
}

// Called when the game starts or when spawned
void AWater::BeginPlay()
{
	Super::BeginPlay();
	mesh->OnComponentBeginOverlap.AddDynamic(this, &AWater::OnOverlapBegin);
}

// Called every frame
void AWater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWater::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (Cast<ATank>(OtherActor)) {
		UExplodableComponent* explodeComp = OtherActor->FindComponentByClass<UExplodableComponent>();

		if (explodeComp) {
			explodeComp->Explode();
		}
	}
}

