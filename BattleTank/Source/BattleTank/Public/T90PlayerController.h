// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "T90.h"
#include "GameFramework/PlayerController.h"
#include "T90PlayerController.generated.h"	//必须是最后一行include语句

/**
 * 
 */
UCLASS()
class BATTLETANK_API AT90PlayerController : public APlayerController
{
	GENERATED_BODY()
	  
public:
	//override:重写父类的virtual方法，且自身也是virtual方法
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	AT90* GetControlledTank() const;	//const:限制类成员不能被修改
	void AimTowardsCrosshair();			//移动炮管至准心方向
	bool GetSightRayHitLocation(FVector& hitLocation) const;	//获取准心位置
	bool GetLookVectorHitLocation(FVector lookDirection, FVector &hitLocation) const;	//根据视点方向返回射线检测点坐标
private:
	//准心水平位置百分比
	UPROPERTY(EditAnywhere)
	int32 crosshairXLocation;
	//准心垂直位置百分比
	UPROPERTY(EditAnywhere)
	int32 crosshairYLocation;
	//射线检测距离
	UPROPERTY(EditAnywhere)
	float lineTraceRange = 1000000;	//UE4的长度单位为cm
};
