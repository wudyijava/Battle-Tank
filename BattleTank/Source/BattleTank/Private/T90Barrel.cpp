// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "T90Barrel.h"

 void UT90Barrel::Elevate(float relativeSpeed)
{
	 //���Ƶ����ٶ�
	 relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, 1);
	 //��֡����ת������
	 auto elevationChange = relativeSpeed * maxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
	 //����ڸ������������Ƕ�
	 auto rawNewElevation = RelativeRotation.Pitch + elevationChange;
	 //Լ���ڼ��޽Ƕ���
	 auto newElevation = FMath::Clamp<float>(rawNewElevation, minElevationDegrees, maxElevationDegrees);

	 SetRelativeRotation(FRotator(newElevation, 0, 0));
}
