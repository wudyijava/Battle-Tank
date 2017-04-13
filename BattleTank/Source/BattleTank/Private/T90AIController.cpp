// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "T90AimingComponent.h"
#include "T90AIController.h"

void AT90AIController::BeginPlay()
{
	Super::BeginPlay();
}

void AT90AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto controlledTank =GetPawn();

	//向角色坦克移动
	MoveToActor(playerTank, accessRadius);

	auto t90AimingComponent = controlledTank->FindComponentByClass<UT90AimingComponent>();
	//瞄准角色坦克
	t90AimingComponent->AimAt(playerTank->GetActorLocation());
	//开火
	t90AimingComponent->Fire();
}