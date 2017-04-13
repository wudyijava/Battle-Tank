// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "T90AimingComponent.generated.h"

//射击状态
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

class UT90Barrel;	//前置声明
class UT90Turret;
class AProjectile;

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

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState firingState = EFiringState::Aiming;	//初始开火状态
public:	

	void AimAt(FVector hitLocation);	//瞄准
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();					//开火

	//设置炮塔与炮塔
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UT90Barrel *barrelToSet, UT90Turret *turretToSet);

private:
	UT90Barrel *barrel = nullptr;
	UT90Turret *turret = nullptr;
	UPROPERTY(EditAnywhere, Category = "Firing")
	float launchSpeed = 5000.0;	//初始速率为50m/s

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> projectileBlueprint;	//炮弹
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float reloadTimeInSeconds = 3;	//炮弹装填时间
	double lastFireTime = 0;		//最近开火时间

	void MoveBarrelTowards(FVector aimDirection);	//调整炮管至指定方向
};
