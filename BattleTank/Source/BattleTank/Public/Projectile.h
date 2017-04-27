// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchProjectile(float speed);		//��ָ���ٶ�ִ�������˶�

private:
	UProjectileMovementComponent *projectileMovement = nullptr;	//�������

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent *collisionMesh = nullptr;		//��ײ�����
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent *launchBlast = nullptr;	//�����������
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent *impactBlast = nullptr;	//��ײ��ը����
	UPROPERTY(VisibleAnywhere, Category = "Components")
	URadialForceComponent *explosionForce = nullptr;	//��ը��
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float destroyDelay = 10.0f;							//��ը������ʱ����ʱ��
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float projectileDamage = 20;						//�ڵ�����

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void OnTimerExpire();
};
