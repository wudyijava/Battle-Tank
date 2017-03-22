// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Rotate_Turret", this, &ATank::RotateTurret);
	PlayerInputComponent->BindAxis("Elevate_Turret", this, &ATank::RotateBarrel);
	PlayerInputComponent->BindAxis("Move_Tank", this, &ATank::MoveTank);
	PlayerInputComponent->BindAxis("Rotate_Tank", this, &ATank::RotateTank);
}

void ATank::RotateTurret(float speed) {
	if (!turret) return;
	auto rotation = GetWorld()->GetDeltaSeconds() * speed * rotationRate;
	turret->AddRelativeRotation(FRotator(0, rotation, 0));
}

void ATank::RotateBarrel(float speed)
{
	if (!barrel) return;
	auto rotation = GetWorld()->GetDeltaSeconds() * speed * rotationRate;
	barrel->AddRelativeRotation(FRotator(rotation, 0, 0));
}

void ATank::MoveTank(float speed)
{
	if (!tank) return;
	auto distance = GetWorld()->GetDeltaSeconds() * speed * movementRate;
	//更新到正方向一定比例的位置为新的位置
	tank->AddRelativeLocation(tank->GetForwardVector() * distance);
}

void ATank::RotateTank(float speed)
{
	if (!tank) return;
	auto rotation = GetWorld()->GetDeltaSeconds() * speed * rotationRate;
	tank->AddRelativeRotation(FRotator(0, rotation, 0));
}

void ATank::SetTurretChildActor(UChildActorComponent * turretFromBP)
{
	turret = turretFromBP;
}

void ATank::SetBarrelChildActor(UChildActorComponent * barrelFromBP)
{
	barrel = barrelFromBP;
}

void ATank::SetTankChildActor(UChildActorComponent * tankFromBP)
{
	tank = tankFromBP;
}

