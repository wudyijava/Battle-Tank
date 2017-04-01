// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "T90Turret.h"


void UT90Turret::Azimuth(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, 1);
	auto rotationChange = relativeSpeed * maxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
	auto newYaw = RelativeRotation.Yaw + rotationChange;
	SetRelativeRotation(FRotator(0, newYaw, 0));
}
