// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "T90MovementComponent.generated.h"

class UT90Track;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UT90MovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UT90Track *leftTrackToSet, UT90Track *rightTrackToSet);	//�����Ĵ�

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float throttle);		//ǰ���ƶ�
	
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnRight(float throttle);	//����ת��

	//��ĳ��Ŀ���ƶ���AIController��Ѱ·�߼���ص��������
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
private:
	UT90Track *leftTrack = nullptr;
	UT90Track *rightTrack = nullptr;
};
