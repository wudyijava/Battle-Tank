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
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UT90AimingComponent::BeginPlay()
{
	Super::BeginPlay();
	lastFireTime = FPlatformTime::Seconds();
}


void UT90AimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (roundsLeft <= 0)
	{
		firingState = EFiringState::OutOfAmmo;
	}
	//炮弹是否装填完毕（时间间隔是否足够）
	else if ((FPlatformTime::Seconds() - lastFireTime) < reloadTimeInSeconds)
	{
		firingState = EFiringState::Reloading;
	} 
	else if (IsBarrelMoving())
	{
		firingState = EFiringState::Aiming;
	} 
	else
	{
		firingState = EFiringState::Locked;
	}
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
		aimDirection = outLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards();
	}
}

void UT90AimingComponent::Initialize(UT90Barrel *barrelToSet, UT90Turret * turretToSet)
{
	if (!ensure(barrelToSet && turretToSet)) return;
	barrel = barrelToSet;
	turret = turretToSet;
}

EFiringState UT90AimingComponent::GetFiringState() const
{
	return firingState;
}

int UT90AimingComponent::GetRoundsLeft() const
{
	return roundsLeft;
}

void UT90AimingComponent::MoveBarrelTowards()
{
	auto barrleRotator = barrel->GetForwardVector().Rotation();	//炮管当前角度
	auto aimAsRotator = aimDirection.Rotation();	//目标方向角度
	auto deltaRotator = aimAsRotator - barrleRotator;	//角度差

	barrel->Elevate(deltaRotator.Pitch);	//炮管只控制仰角
	//炮塔控制水平旋转
	if (FMath::Abs<float>(deltaRotator.Yaw) < 180)
	{
		turret->Azimuth(deltaRotator.Yaw);
	}
	else
	{
		turret->Azimuth(-deltaRotator.Yaw);
	}
}

bool UT90AimingComponent::IsBarrelMoving()
{
	if (!ensure(barrel)) return false;
	auto barrelForward = barrel->GetForwardVector();
	return !barrelForward.Equals(aimDirection, 0.01f);
}

void UT90AimingComponent::Fire()
{
	if (!ensure(barrel && projectileBlueprint)) return;

	if (firingState == EFiringState::Aiming || firingState == EFiringState::Locked ) {
		auto projectile = GetWorld()->SpawnActor<AProjectile>(
			projectileBlueprint,	//蓝图类模板，类似Unity中的预制体
			barrel->GetSocketLocation(FName("Projectile")),
			barrel->GetSocketRotation(FName("Projectile"))
			);						//创建炮弹
		projectile->LaunchProjectile(launchSpeed);	//发射炮弹
		lastFireTime = FPlatformTime::Seconds();	//更新最近开火时间
		roundsLeft--;				//消耗一枚炮弹
	}
}
