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
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float throttle);

	void DriveTrack();

	void ApplySidiewayForce();
	
private:
	UPROPERTY(EditDefaultsOnly)
	float maxTrackDrivingForce = 90000000;	//承受45吨的坦克和2克加速度
	float currentThrottle = 0;				//驱动力系数

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
