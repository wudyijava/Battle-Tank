    // Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(collisionMesh);		//设为根组件
	collisionMesh->SetNotifyRigidBodyCollision(true);	//打开Simulation Generates Hit Events
	collisionMesh->SetVisibility(false);

	launchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	launchBlast->AttachTo(RootComponent);

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	projectileMovement->SetAutoActivate(false);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float speed)
{
	projectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	projectileMovement->Activate();
}

