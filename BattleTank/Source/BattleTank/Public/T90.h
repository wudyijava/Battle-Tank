// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "T90AimingComponent.h"
#include "GameFramework/Pawn.h"
#include "T90.generated.h"

class UT90Barrel;
class UT90Turret;

UCLASS()
class BATTLETANK_API AT90 : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AT90();

protected:
	UT90AimingComponent *t90AimingComponent = nullptr;	//注意初始化

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector hitLocation);	//炮管向准心瞄准

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UT90Barrel *barrelToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UT90Turret *turretToSet);
	
	UPROPERTY(EditAnywhere, Category=Firing)
	float launchSpeed = 50000.0;	//初始速率为500m/s
};
