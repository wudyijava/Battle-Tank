// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//通过蓝图注入炮塔参数
	UFUNCTION(BlueprintCallable, Category = Tank)
	void SetTurretChildActor(UChildActorComponent* turretFromBP);

	//通过蓝图注入炮管参数
	UFUNCTION(BlueprintCallable, Category = Tank)
	void SetBarrelChildActor(UChildActorComponent* barrelFromBP);

	//通过蓝图注入坦克参数
	UFUNCTION(BlueprintCallable, Category = Tank)
	void SetTankChildActor(UChildActorComponent* tankFromBP);
private:
	UChildActorComponent* turret;	//存放炮塔对象
	UChildActorComponent* barrel;	//存放炮管对象
	UChildActorComponent* tank;		//存放坦克车身对象
	UPROPERTY(EditAnywhere)
	float movementRate = 1200.0f;		//车身移动速率
	UPROPERTY(EditAnywhere)
	float rotationRate = 120.0f;		//车身转向速率

	void RotateTurret(float);	//旋转炮塔
	void RotateBarrel(float);	//旋转炮管
	void MoveTank(float);		//车身前后移动
	void RotateTank(float);		//车身转向
};
