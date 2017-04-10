// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "T90.h"
#include "T90AIController.h"

void AT90AIController::BeginPlay()
{
	Super::BeginPlay();
}

void AT90AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto playerTank = Cast<AT90>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto controlledTank = Cast<AT90>(GetPawn());

	//瞄准角色坦克
	controlledTank->AimAt(playerTank->GetActorLocation());
	//开火
	controlledTank->Fire();
}