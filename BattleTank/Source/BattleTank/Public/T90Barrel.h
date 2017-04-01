// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "T90Barrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), hidecategories=("Collision"))
class BATTLETANK_API UT90Barrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float relativeSpeed);	//改变炮管仰角
	
private:
	UPROPERTY(EditAnywhere, Category=Setup)
	float maxDegreesPerSecond = 10;	//每秒旋转角度
	
	UPROPERTY(EditAnywhere, Category = Setup)
	float minElevationDegrees = -5;	//最小旋转角度
	UPROPERTY(EditAnywhere, Category = Setup)
	float maxElevationDegrees = 40;	//最大旋转角度

};
