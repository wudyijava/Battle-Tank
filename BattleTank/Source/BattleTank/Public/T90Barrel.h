// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "T90Barrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UT90Barrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float relativeSpeed);	//�ı��ڹ�����
	
private:
	UPROPERTY(EditDefaultsOnly, Category=Setup)
	float maxDegreesPerSecond = 10;	//ÿ����ת�Ƕ�
	
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float minElevationDegrees = -5;	//��С��ת�Ƕ�
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float maxElevationDegrees = 40;	//�����ת�Ƕ�

};
