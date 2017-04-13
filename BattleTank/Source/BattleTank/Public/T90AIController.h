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
	float accessRadius = 3000;	//Í¨¹ý°ë¾¶cm
};
