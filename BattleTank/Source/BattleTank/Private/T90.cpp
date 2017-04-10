// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "T90Barrel.h"
#include "Projectile.h"
#include "T90.h"
#include "T90AimingComponent.h"

// Sets default values
AT90::AT90()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	t90AimingComponent = CreateDefaultSubobject<UT90AimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void AT90::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void AT90::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AT90::AimAt(FVector hitLocation)
{
	t90AimingComponent->AimAt(hitLocation, launchSpeed);
}

void AT90::Fire()
{
	//炮弹是否装填完毕（时间间隔是否足够）
	bool isReloaded = (FPlatformTime::Seconds() - lastFireTime) > reloadTimeInSeconds;

	if (barrel && isReloaded) {
		auto projectile = GetWorld()->SpawnActor<AProjectile>(
			projectileBlueprint,	//蓝图类模板，类似Unity中的预制体
			barrel->GetSocketLocation(FName("Projectile")),
			barrel->GetSocketRotation(FName("Projectile"))
			);						//创建炮弹
		projectile->LaunchProjectile(launchSpeed);	//发射炮弹
		lastFireTime = FPlatformTime::Seconds();	//更新最近开火时间
	}
}

void AT90::SetBarrelReference(UT90Barrel *barrelToSet)
{
	t90AimingComponent->SetBarrelReference(barrelToSet);
	barrel = barrelToSet;
}

void AT90::SetTurretReference(UT90Turret * turretToSet)
{
	t90AimingComponent->SetTurretReference(turretToSet);
}

