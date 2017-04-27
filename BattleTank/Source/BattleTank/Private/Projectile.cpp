    // Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	collisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(collisionMesh);		//设为根组件
	collisionMesh->SetNotifyRigidBodyCollision(true);	//打开Simulation Generates Hit Events
	
	launchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	launchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	impactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Balst"));
	impactBlast->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);
	impactBlast->SetAutoActivate(false);

	explosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	explosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	projectileMovement->SetAutoActivate(false);

	collisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
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

void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	launchBlast->Deactivate();			//禁用发射粒子
	impactBlast->Activate();			//启用碰撞爆炸粒子
	explosionForce->FireImpulse();		//释放冲击力

	SetRootComponent(impactBlast);		//替换根组件为爆炸粒子（它还需播放一段时间）
	collisionMesh->DestroyComponent();	//以删除网格物体

	//伤害计算
	UGameplayStatics::ApplyRadialDamage(
		this,							//上下文
		projectileDamage,				//基本破坏
		GetActorLocation(),				//爆炸中心
		explosionForce->Radius,			//范围半径
		UDamageType::StaticClass(),		//波及类型
		TArray<AActor *>()				//免疫类型
	);

	//等待destroyDelay时间后通过OnTimerExpire函数删除根物体（爆炸粒子）
	FTimerHandle timer;
	GetWorld()->GetTimerManager().SetTimer(timer, this, &AProjectile::OnTimerExpire, destroyDelay);
}

void AProjectile::OnTimerExpire()
{
	Destroy();
}

