// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "T90Track.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom),meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UT90Track : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float throttle);
	
private:
	UPROPERTY(EditDefaultsOnly)
	float maxTrackDrivingForce = 45000000;	//承受45吨的坦克和1克加速度
};
