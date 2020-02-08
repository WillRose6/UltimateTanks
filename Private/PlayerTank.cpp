// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTank.h"
#include "UltimateTanksGameModeBase.h"

APlayerTank::APlayerTank() {
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void APlayerTank::BeginPlay() {
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(GetController());
}

void APlayerTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult hit;
	PlayerController->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, false, hit);

	FVector direction = hit.ImpactPoint - GetActorLocation();
	FRotator rot = FRotator(0, direction.Rotation().Yaw, 0);
	CannonMesh->SetRelativeRotation(rot);
}

void APlayerTank::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerTank::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerTank::MoveRight);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerTank::Fire);
}

void APlayerTank::MoveForward(float Value)
{
	if ((Controller) && (Value != 0.0f)) {
		const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
		FVector2D inputs = FVector2D(InputComponent->GetAxisValue("MoveForward"), InputComponent->GetAxisValue("MoveRight"));
		RotateTowardsMovementDirection(inputs);
	}
}

void APlayerTank::MoveRight(float Value)
{
	if ((Controller) && (Value != 0.0f)) {
		const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
		FVector2D inputs = FVector2D(InputComponent->GetAxisValue("MoveForward"), InputComponent->GetAxisValue("MoveRight"));
		RotateTowardsMovementDirection(inputs);
	}
}

void APlayerTank::ReadyToFire() {
	Super::ReadyToFire();
}

void APlayerTank::OnDestroyTank()
{
	Super::OnDestroyTank();
	Cast<AUltimateTanksGameModeBase>(GetWorld()->GetAuthGameMode())->PlayerDied();
}

