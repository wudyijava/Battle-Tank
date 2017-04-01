// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "T90Barrel.h"

 void UT90Barrel::Elevate(float relativeSpeed)
{
	 //限制单步速度
	 relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, 1);
	 //单帧的旋转步进量
	 auto elevationChange = relativeSpeed * maxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
	 //相对于父物体的新上扬角度
	 auto rawNewElevation = RelativeRotation.Pitch + elevationChange;
	 //约束在极限角度内
	 auto newElevation = FMath::Clamp<float>(rawNewElevation, minElevationDegrees, maxElevationDegrees);

	 SetRelativeRotation(FRotator(newElevation, 0, 0));
}
