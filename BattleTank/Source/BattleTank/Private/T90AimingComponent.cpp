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
	auto barrleRotator = barrel->GetForwardVector().Rotation();	//�ڹܵ�ǰ�Ƕ�
	auto aimAsRotator = aimDirection.Rotation();	//Ŀ�귽��Ƕ�
	auto deltaRotator = aimAsRotator - barrleRotator;	//�ǶȲ�

	barrel->Elevate(deltaRotator.Pitch);	//�ڹ�ֻ��������
	turret->Azimuth(deltaRotator.Yaw);		//��������ˮƽ��ת
}

