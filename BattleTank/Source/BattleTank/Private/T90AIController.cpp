// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "T90AimingComponent.h"
#include "T90.h"
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
	MoveToActor(playerTank, acceptanceRadius);

	auto t90AimingComponent = controlledTank->FindComponentByClass<UT90AimingComponent>();
	//瞄准角色坦克
	t90AimingComponent->AimAt(playerTank->GetActorLocation());
	//开火
	if (t90AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		t90AimingComponent->Fire();
	}
}

void AT90AIController::OnPossedT90Death()
{
	if (ensure(!GetPawn())) return;
	GetPawn()->DetachFromControllerPendingDestroy();	//当被销毁时脱离控制
}

void AT90AIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto possessedTank = Cast<AT90>(InPawn);
		if (!ensure(possessedTank)) return;
		possessedTank->OnDeath.AddUniqueDynamic(this, &AT90AIController::OnPossedT90Death);
	}
}
