// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "T90.generated.h"

class UT90Barrel;
class UT90Turret;
class AProjectile;
class UT90AimingComponent;

UCLASS()
class BATTLETANK_API AT90 : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category=Firing)
	float launchSpeed = 5000.0;	//��ʼ����Ϊ50m/s
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> projectileBlueprint;	//�ڵ�

	UT90Barrel *barrel = nullptr;	//�����ڵ���Ҫ�ڹܶ�λ��ʼλ��

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float reloadTimeInSeconds = 3;	//�ڵ�װ��ʱ��
	double lastFireTime = 0;		//�������ʱ��

public:
	// Sets default values for this pawn's properties
	AT90();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector hitLocation);	//�ڹ���׼����׼

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UT90Barrel *barrelToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UT90Turret *turretToSet);
	UFUNCTION(BlueprintCallable, Category=Firing)
	void Fire();					//����

protected:
	UT90AimingComponent *t90AimingComponent = nullptr;	//ע���ʼ��

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
