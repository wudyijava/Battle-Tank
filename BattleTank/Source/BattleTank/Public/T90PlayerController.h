// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "T90PlayerController.generated.h"	//���������һ��include���

class UT90AimingComponent;

UCLASS()
class BATTLETANK_API AT90PlayerController : public APlayerController
{
	GENERATED_BODY()
	  
public:
	//override:��д�����virtual������������Ҳ��virtual����
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	//����һ����ͼ�¼�������׼������ݵ���ͼ
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UT90AimingComponent *aimingComponent);

	void AimTowardsCrosshair();			//�ƶ��ڹ���׼�ķ���
	bool GetSightRayHitLocation(FVector& hitLocation) const;	//��ȡ׼��λ��
	bool GetLookVectorHitLocation(FVector lookDirection, FVector &hitLocation) const;	//�����ӵ㷽�򷵻����߼�������
private:
	//׼��ˮƽλ�ðٷֱ�
	UPROPERTY(EditDefaultsOnly)
	float crosshairXLocation = 0.5f;
	//׼�Ĵ�ֱλ�ðٷֱ�
	UPROPERTY(EditDefaultsOnly)
	float crosshairYLocation = 0.3333f;
	//���߼�����
	UPROPERTY(EditDefaultsOnly)
	float lineTraceRange = 1000000;	//UE4�ĳ��ȵ�λΪcm
};
