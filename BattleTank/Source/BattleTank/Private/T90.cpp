// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "T90.h"


// Sets default values
AT90::AT90()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AT90::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AT90::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AT90::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AT90::AimAt(FVector hitLocation)
{
	UE_LOG(LogTemp, Warning, TEXT("%s aim at : %s"), *GetName(), *hitLocation.ToString());
}

