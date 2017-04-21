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
	Locked,
	OutOfAmmo
};

class UT90Barrel;	//前置声明
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
	EFiringState firingState = EFiringState::Reloading;	//初始开火状态

public:	
	// Sets default values for this component's properties
	UT90AimingComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void AimAt(FVector hitLocation);	//瞄准
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();					//开火

	//设置炮塔与炮塔
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UT90Barrel *barrelToSet, UT90Turret *turretToSet);

	EFiringState GetFiringState() const;
	UFUNCTION(BlueprintCallable, Category = "Firing")
	int GetRoundsLeft() const;

private:
	UT90Barrel *barrel = nullptr;
	UT90Turret *turret = nullptr;
	FVector aimDirection;			//目标方向
	UPROPERTY(EditAnywhere, Category = "Firing")
	float launchSpeed = 5000.0;	//初始速率为50m/s

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> projectileBlueprint;	//炮弹
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float reloadTimeInSeconds = 3;	//炮弹装填时间
	double lastFireTime = 0;		//最近开火时间
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int roundsLeft = 3;				//剩余弹量

	void MoveBarrelTowards();		//调整炮管至指定方向
	bool IsBarrelMoving();			//是否已转向目标
};
