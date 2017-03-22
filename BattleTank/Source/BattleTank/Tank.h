// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//ͨ����ͼע����������
	UFUNCTION(BlueprintCallable, Category = Tank)
	void SetTurretChildActor(UChildActorComponent* turretFromBP);

	//ͨ����ͼע���ڹܲ���
	UFUNCTION(BlueprintCallable, Category = Tank)
	void SetBarrelChildActor(UChildActorComponent* barrelFromBP);

	//ͨ����ͼע��̹�˲���
	UFUNCTION(BlueprintCallable, Category = Tank)
	void SetTankChildActor(UChildActorComponent* tankFromBP);
private:
	UChildActorComponent* turret;	//�����������
	UChildActorComponent* barrel;	//����ڹܶ���
	UChildActorComponent* tank;		//���̹�˳������
	UPROPERTY(EditAnywhere)
	float movementRate = 1200.0f;		//�����ƶ�����
	UPROPERTY(EditAnywhere)
	float rotationRate = 120.0f;		//����ת������

	void RotateTurret(float);	//��ת����
	void RotateBarrel(float);	//��ת�ڹ�
	void MoveTank(float);		//����ǰ���ƶ�
	void RotateTank(float);		//����ת��
};
