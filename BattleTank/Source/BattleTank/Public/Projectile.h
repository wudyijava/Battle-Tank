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

	void LaunchProjectile(float speed);		//按指定速度执行抛掷运动

private:
	UProjectileMovementComponent *projectileMovement = nullptr;	//抛掷组件

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent *collisionMesh = nullptr;		//碰撞体组件
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent *launchBlast = nullptr;	//发射火焰粒子
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent *impactBlast = nullptr;	//碰撞爆炸粒子
	UPROPERTY(VisibleAnywhere, Category = "Components")
	URadialForceComponent *explosionForce = nullptr;	//爆炸力
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float destroyDelay = 10.0f;							//爆炸粒子延时销毁时长
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float projectileDamage = 20;						//炮弹威力

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void OnTimerExpire();
};
