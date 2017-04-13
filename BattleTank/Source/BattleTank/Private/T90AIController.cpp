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

	//���ɫ̹���ƶ�
	MoveToActor(playerTank, accessRadius);

	auto t90AimingComponent = controlledTank->FindComponentByClass<UT90AimingComponent>();
	//��׼��ɫ̹��
	t90AimingComponent->AimAt(playerTank->GetActorLocation());
	//����
	t90AimingComponent->Fire();
}