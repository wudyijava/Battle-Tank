// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "T90Barrel.h"
#include "T90Turret.h"
#include "T90AimingComponent.h"


// Sets default values for this component's properties
UT90AimingComponent::UT90AimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UT90AimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UT90AimingComponent::AimAt(FVector hitLocation, float launchSpeed)
{
	if (!barrel) return;

	FVector outLaunchVelocity;
	FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));

	auto bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		outLaunchVelocity,	//抛掷速度结果
		startLocation,		//源点坐标
		hitLocation,		//终点坐标
		launchSpeed,		//投掷速率
		false,				//高抛弧线
		0,					//碰撞半径
		0,					//重塑重力
		ESuggestProjVelocityTraceOption::DoNotTrace	//无跟踪轨迹
	);
	if (bHaveAimSolution)
	{
		auto aimDirection = outLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(aimDirection);
	}
}

void UT90AimingComponent::SetBarrelReference(UT90Barrel *barrelToSet)
{
	if (!barrelToSet) return;
	barrel = barrelToSet;
}

void UT90AimingComponent::SetTurretReference(UT90Turret * turretToSet)
{
	if (!turretToSet) return;
	turret = turretToSet;
}

void UT90AimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	auto barrleRotator = barrel->GetForwardVector().Rotation();	//炮管当前角度
	auto aimAsRotator = aimDirection.Rotation();	//目标方向角度
	auto deltaRotator = aimAsRotator - barrleRotator;	//角度差

	barrel->Elevate(deltaRotator.Pitch);	//炮管只控制仰角
	turret->Azimuth(deltaRotator.Yaw);		//炮塔控制水平旋转
}

