// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "T90AimingComponent.h"
#include "T90.h"
#include "T90PlayerController.h"

void AT90PlayerController::BeginPlay()
{
	Super::BeginPlay();	//��Ҫ��©

	aimingComponent = GetPawn()->FindComponentByClass<UT90AimingComponent>();
	if (!aimingComponent) return;
	FoundAimingComponent(aimingComponent);
}

void AT90PlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
} 


void AT90PlayerController::OnPossedT90Death()
{
	//StartSpectatingOnly();	//��������ʱ�����Թ�ģʽ���ؿ���NPC̹�˻����ˣ�
}

void AT90PlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto possessedTank = Cast<AT90>(InPawn);
		if (!ensure(possessedTank)) return;
		possessedTank->OnDeath.AddUniqueDynamic(this, &AT90PlayerController::OnPossedT90Death);
	}
}


void AT90PlayerController::AimTowardsCrosshair() {
	//����������ȡaimingComponent����ʹ�õ�4.15.0�汾���ڴ�T90_PlayerController_BPʱ����
	//auto aimingComponent = GetPawn()->FindComponentByClass<UT90AimingComponent>();
	if (!aimingComponent) return;

	FVector hitLocation;
	if (GetSightRayHitLocation(hitLocation))
	{
		aimingComponent->AimAt(hitLocation);	//����̹�˵���׼����
	}
}

bool AT90PlayerController::GetSightRayHitLocation(FVector& hitLocation) const
{
	//��ȡ��Ļ���ش�С
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);
	//���׼�ĵ���Ļλ��
	auto screenLocation = FVector2D(viewportSizeX * crosshairXLocation, viewportSizeY * crosshairYLocation);

	FVector cameraWorldLocation;
	FVector worldDirection;
	//ת����Ļ����������ռ��е�����ʼ���뷽��
	if (DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, cameraWorldLocation, worldDirection))
	{
		return GetLookVectorHitLocation(worldDirection, hitLocation);
	}
	return false;
}

bool AT90PlayerController::GetLookVectorHitLocation(FVector lookDirection, FVector &hitLocation) const {
	FHitResult hitResult;
	auto startLocation = PlayerCameraManager->GetCameraLocation();
	auto endLocation = startLocation + (lookDirection * lineTraceRange);
	bool hasPickup = GetWorld()->LineTraceSingleByChannel(
		hitResult,
		startLocation,
		endLocation,
		ECollisionChannel::ECC_Camera);
	if (hasPickup)
	{
		hitLocation = hitResult.Location;
		return true;
	}
	hitLocation = FVector(0);
	return false;
}
