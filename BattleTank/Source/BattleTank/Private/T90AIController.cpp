// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "T90AIController.h"

void AT90AIController::BeginPlay()
{
	Super::BeginPlay();

	auto controlledTank = GetControlledTank();
	if (!controlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI controller not possessing a tank."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI controller possessing: %s"), *controlledTank->GetName());
	}
}

void AT90AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Ãé×¼½ÇÉ«Ì¹¿Ë
	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}

AT90* AT90AIController::GetControlledTank() const {
	return Cast<AT90>(GetPawn());
}

AT90* AT90AIController::GetPlayerTank() const {
	auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if(!playerPawn) return nullptr;
	return Cast<AT90>(playerPawn);
}
