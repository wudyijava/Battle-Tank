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
	float launchSpeed = 5000.0;	//初始速率为50m/s
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> projectileBlueprint;	//炮弹

	UT90Barrel *barrel = nullptr;	//发射炮弹需要炮管定位初始位置

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float reloadTimeInSeconds = 3;	//炮弹装填时间
	double lastFireTime = 0;		//最近开火时间

public:
	// Sets default values for this pawn's properties
	AT90();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector hitLocation);	//炮管向准心瞄准

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UT90Barrel *barrelToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UT90Turret *turretToSet);
	UFUNCTION(BlueprintCallable, Category=Firing)
	void Fire();					//开火

protected:
	UT90AimingComponent *t90AimingComponent = nullptr;	//注意初始化

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
