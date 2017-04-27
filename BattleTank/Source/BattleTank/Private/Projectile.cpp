    // Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	collisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(collisionMesh);		//��Ϊ�����
	collisionMesh->SetNotifyRigidBodyCollision(true);	//��Simulation Generates Hit Events
	
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
	launchBlast->Deactivate();			//���÷�������
	impactBlast->Activate();			//������ײ��ը����
	explosionForce->FireImpulse();		//�ͷų����

	SetRootComponent(impactBlast);		//�滻�����Ϊ��ը���ӣ������貥��һ��ʱ�䣩
	collisionMesh->DestroyComponent();	//��ɾ����������

	//�˺�����
	UGameplayStatics::ApplyRadialDamage(
		this,							//������
		projectileDamage,				//�����ƻ�
		GetActorLocation(),				//��ը����
		explosionForce->Radius,			//��Χ�뾶
		UDamageType::StaticClass(),		//��������
		TArray<AActor *>()				//��������
	);

	//�ȴ�destroyDelayʱ���ͨ��OnTimerExpire����ɾ�������壨��ը���ӣ�
	FTimerHandle timer;
	GetWorld()->GetTimerManager().SetTimer(timer, this, &AProjectile::OnTimerExpire, destroyDelay);
}

void AProjectile::OnTimerExpire()
{
	Destroy();
}

