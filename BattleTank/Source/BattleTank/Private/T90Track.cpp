// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "T90Track.h"

void UT90Track::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UT90Track::OnHit);
}

void UT90Track::SetThrottle(float throttle)
{
	currentThrottle = FMath::Clamp<float>(currentThrottle + throttle, -1, 1);
}

void UT90Track::DriveTrack()
{
	//将输入值转换为驱动力
	auto forceApplied = GetForwardVector() * currentThrottle * maxTrackDrivingForce;
	//获得坦克本体
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//着力点在履带的坐标
	tankRoot->AddForceAtLocation(forceApplied, GetComponentLocation());
}

void UT90Track::ApplySidiewayForce()
{
	//计算打滑速度（将当前速度映射到侧向力）
	auto slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto deltaTime = GetWorld()->DeltaTimeSeconds;
	auto correctionAcceleration = -slippageSpeed / deltaTime * GetRightVector();	//反向摩擦力

	auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto correctionFoce = (tankRoot->GetMass() * correctionAcceleration) / 2;	//两条履带
	tankRoot->AddForce(correctionFoce);

}

void UT90Track::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	ApplySidiewayForce();
	currentThrottle = 0;	//累加系数清零
}
