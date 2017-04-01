// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "T90Turret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom),meta=(BlueprintSpawnableComponent),hidecategories=("Collision"))
class BATTLETANK_API UT90Turret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Azimuth(float relativeSpeed);
	
private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float maxDegreesPerSecond = 20;	//Ã¿ÃëÐý×ª½Ç¶È
};
