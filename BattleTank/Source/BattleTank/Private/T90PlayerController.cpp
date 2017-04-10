// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "T90PlayerController.h"

void AT90PlayerController::BeginPlay()
{
	Super::BeginPlay();	//不要遗漏

	auto controlledTank = GetControlledTank();
	if (!controlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller not possessing a tank."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller possessing: %s"), *controlledTank->GetName());
	}
}

void AT90PlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

AT90* AT90PlayerController::GetControlledTank() const {
	return Cast<AT90>(GetPawn());
}

void AT90PlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) return;

	FVector hitLocation;
	if (GetSightRayHitLocation(hitLocation) && hitLocation != FVector(0))
	{
		GetControlledTank()->AimAt(hitLocation);	//调用坦克的瞄准方法
	}
}

bool AT90PlayerController::GetSightRayHitLocation(FVector& hitLocation) const
{
	//获取屏幕像素大小
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);
	//获得准心的屏幕位置
	auto screenLocation = FVector2D(viewportSizeX * crosshairXLocation, viewportSizeY * crosshairYLocation);

	FVector cameraWorldLocation;
	FVector worldDirection;
	//转换屏幕坐标在世界空间中的射线始点与方向
	if (DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, cameraWorldLocation, worldDirection))
	{
		GetLookVectorHitLocation(worldDirection, hitLocation);
	}
	return true;
}

bool AT90PlayerController::GetLookVectorHitLocation(FVector lookDirection, FVector &hitLocation) const {
	FHitResult hitResult;
	auto startLocation = PlayerCameraManager->GetCameraLocation();
	auto endLocation = startLocation + (lookDirection * lineTraceRange);
	bool hasPickup = GetWorld()->LineTraceSingleByChannel(
		hitResult,
		startLocation,
		endLocation,
		ECollisionChannel::ECC_Visibility);
	if (hasPickup)
	{
		hitLocation = hitResult.Location;
		return true;
	}
	hitLocation = FVector(0);
	return false;
}
