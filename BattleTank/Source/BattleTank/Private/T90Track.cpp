// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "T90Track.h"

void UT90Track::SetThrottle(float throttle)
{
	//TODO 离地状态也能施加力（碰撞检测）
	FHitResult hitResult;
	auto startLocation = GetComponentLocation();
	auto endLocation = startLocation + (FVector::UpVector * -100);
	bool hasPickup = GetWorld()->LineTraceSingleByChannel(
		hitResult,
		startLocation,
		endLocation,
		ECollisionChannel::ECC_Visibility);
	if (!hasPickup) return;

	//将输入值转换为驱动力
	auto forceApplied = GetForwardVector() * throttle * maxTrackDrivingForce;
	//获得坦克本体
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//着力点在履带的坐标
	tankRoot->AddForceAtLocation(forceApplied, GetComponentLocation());
}
