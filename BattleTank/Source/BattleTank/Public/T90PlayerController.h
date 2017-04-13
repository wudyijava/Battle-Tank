// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "T90PlayerController.generated.h"	//必须是最后一行include语句

class UT90AimingComponent;

UCLASS()
class BATTLETANK_API AT90PlayerController : public APlayerController
{
	GENERATED_BODY()
	  
public:
	//override:重写父类的virtual方法，且自身也是virtual方法
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	//定义一个蓝图事件，将瞄准组件传递到蓝图
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UT90AimingComponent *aimingComponent);

	void AimTowardsCrosshair();			//移动炮管至准心方向
	bool GetSightRayHitLocation(FVector& hitLocation) const;	//获取准心位置
	bool GetLookVectorHitLocation(FVector lookDirection, FVector &hitLocation) const;	//根据视点方向返回射线检测点坐标
private:
	//准心水平位置百分比
	UPROPERTY(EditDefaultsOnly)
	float crosshairXLocation = 0.5f;
	//准心垂直位置百分比
	UPROPERTY(EditDefaultsOnly)
	float crosshairYLocation = 0.3333f;
	//射线检测距离
	UPROPERTY(EditDefaultsOnly)
	float lineTraceRange = 1000000;	//UE4的长度单位为cm
};
