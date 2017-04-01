// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "T90AimingComponent.generated.h"

class UT90Barrel;	//ǰ������
class UT90Turret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UT90AimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UT90AimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	void AimAt(FVector hitLocation, float launchSpeed);

	void SetBarrelReference(UT90Barrel *barrelToSet);	//��ȡ�ڹ�
	void SetTurretReference(UT90Turret *turretToSet);	//��ȡ����

private:
	UT90Barrel *barrel = nullptr;
	UT90Turret *turret = nullptr;
	
	void MoveBarrelTowards(FVector aimDirection);	//�����ڹ���ָ������
};
