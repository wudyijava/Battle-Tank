// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "T90AIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API AT90AIController : public AAIController
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnPossedT90Death();	//接收多播的回调，处理坦克销毁
	virtual void SetPawn(APawn* InPawn) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float acceptanceRadius = 3000;	//距离目标需要移动的半径cm
};
