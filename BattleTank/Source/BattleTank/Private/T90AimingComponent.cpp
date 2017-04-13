// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "T90Barrel.h"
#include "T90Turret.h"
#include "Projectile.h"
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
}


void UT90AimingComponent::AimAt(FVector hitLocation)
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

void UT90AimingComponent::Initialize(UT90Barrel *barrelToSet, UT90Turret * turretToSet)
{
	if (!ensure(barrelToSet && turretToSet)) return;
	barrel = barrelToSet;
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


void UT90AimingComponent::Fire()
{
	if (!ensure(barrel && projectileBlueprint)) return;

	//炮弹是否装填完毕（时间间隔是否足够）
	bool isReloaded = (FPlatformTime::Seconds() - lastFireTime) > reloadTimeInSeconds;
	if (isReloaded) {
		auto projectile = GetWorld()->SpawnActor<AProjectile>(
			projectileBlueprint,	//蓝图类模板，类似Unity中的预制体
			barrel->GetSocketLocation(FName("Projectile")),
			barrel->GetSocketRotation(FName("Projectile"))
			);						//创建炮弹
		projectile->LaunchProjectile(launchSpeed);	//发射炮弹
		lastFireTime = FPlatformTime::Seconds();	//更新最近开火时间
	}
}
