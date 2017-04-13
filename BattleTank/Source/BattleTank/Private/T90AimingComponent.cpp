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
		outLaunchVelocity,	//�����ٶȽ��
		startLocation,		//Դ������
		hitLocation,		//�յ�����
		launchSpeed,		//Ͷ������
		false,				//���׻���
		0,					//��ײ�뾶
		0,					//��������
		ESuggestProjVelocityTraceOption::DoNotTrace	//�޸��ٹ켣
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
	auto barrleRotator = barrel->GetForwardVector().Rotation();	//�ڹܵ�ǰ�Ƕ�
	auto aimAsRotator = aimDirection.Rotation();	//Ŀ�귽��Ƕ�
	auto deltaRotator = aimAsRotator - barrleRotator;	//�ǶȲ�

	barrel->Elevate(deltaRotator.Pitch);	//�ڹ�ֻ��������
	turret->Azimuth(deltaRotator.Yaw);		//��������ˮƽ��ת
}


void UT90AimingComponent::Fire()
{
	if (!ensure(barrel && projectileBlueprint)) return;

	//�ڵ��Ƿ�װ����ϣ�ʱ�����Ƿ��㹻��
	bool isReloaded = (FPlatformTime::Seconds() - lastFireTime) > reloadTimeInSeconds;
	if (isReloaded) {
		auto projectile = GetWorld()->SpawnActor<AProjectile>(
			projectileBlueprint,	//��ͼ��ģ�壬����Unity�е�Ԥ����
			barrel->GetSocketLocation(FName("Projectile")),
			barrel->GetSocketRotation(FName("Projectile"))
			);						//�����ڵ�
		projectile->LaunchProjectile(launchSpeed);	//�����ڵ�
		lastFireTime = FPlatformTime::Seconds();	//�����������ʱ��
	}
}
