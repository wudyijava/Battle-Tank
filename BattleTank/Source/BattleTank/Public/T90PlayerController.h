// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "T90.h"
#include "GameFramework/PlayerController.h"
#include "T90PlayerController.generated.h"	//���������һ��include���

/**
 * 
 */
UCLASS()
class BATTLETANK_API AT90PlayerController : public APlayerController
{
	GENERATED_BODY()
	  
public:
	//override:��д�����virtual������������Ҳ��virtual����
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	AT90* GetControlledTank() const;	//const:�������Ա���ܱ��޸�
	void AimTowardsCrosshair();			//�ƶ��ڹ���׼�ķ���
	bool GetSightRayHitLocation(FVector& hitLocation) const;	//��ȡ׼��λ��
	bool GetLookVectorHitLocation(FVector lookDirection, FVector &hitLocation) const;	//�����ӵ㷽�򷵻����߼�������
private:
	//׼��ˮƽλ�ðٷֱ�
	UPROPERTY(EditAnywhere)
	int32 crosshairXLocation;
	//׼�Ĵ�ֱλ�ðٷֱ�
	UPROPERTY(EditAnywhere)
	int32 crosshairYLocation;
	//���߼�����
	UPROPERTY(EditAnywhere)
	float lineTraceRange = 1000000;	//UE4�ĳ��ȵ�λΪcm
};
