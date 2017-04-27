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
	void OnPossedT90Death();	//���նಥ�Ļص�������̹������
	virtual void SetPawn(APawn* InPawn) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float acceptanceRadius = 3000;	//����Ŀ����Ҫ�ƶ��İ뾶cm
};
