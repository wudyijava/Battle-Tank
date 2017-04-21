// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "T90AimingComponent.generated.h"

//���״̬
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

class UT90Barrel;	//ǰ������
class UT90Turret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UT90AimingComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState firingState = EFiringState::Reloading;	//��ʼ����״̬

public:	
	// Sets default values for this component's properties
	UT90AimingComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void AimAt(FVector hitLocation);	//��׼
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();					//����

	//��������������
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UT90Barrel *barrelToSet, UT90Turret *turretToSet);

	EFiringState GetFiringState() const;
	UFUNCTION(BlueprintCallable, Category = "Firing")
	int GetRoundsLeft() const;

private:
	UT90Barrel *barrel = nullptr;
	UT90Turret *turret = nullptr;
	FVector aimDirection;			//Ŀ�귽��
	UPROPERTY(EditAnywhere, Category = "Firing")
	float launchSpeed = 5000.0;	//��ʼ����Ϊ50m/s

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> projectileBlueprint;	//�ڵ�
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float reloadTimeInSeconds = 3;	//�ڵ�װ��ʱ��
	double lastFireTime = 0;		//�������ʱ��
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int roundsLeft = 3;				//ʣ�൯��

	void MoveBarrelTowards();		//�����ڹ���ָ������
	bool IsBarrelMoving();			//�Ƿ���ת��Ŀ��
};
