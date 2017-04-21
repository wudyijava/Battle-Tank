// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "T90Track.h"

void UT90Track::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UT90Track::OnHit);
}

void UT90Track::SetThrottle(float throttle)
{
	currentThrottle = FMath::Clamp<float>(currentThrottle + throttle, -1, 1);
}

void UT90Track::DriveTrack()
{
	//������ֵת��Ϊ������
	auto forceApplied = GetForwardVector() * currentThrottle * maxTrackDrivingForce;
	//���̹�˱���
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//���������Ĵ�������
	tankRoot->AddForceAtLocation(forceApplied, GetComponentLocation());
}

void UT90Track::ApplySidiewayForce()
{
	//������ٶȣ�����ǰ�ٶ�ӳ�䵽��������
	auto slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto deltaTime = GetWorld()->DeltaTimeSeconds;
	auto correctionAcceleration = -slippageSpeed / deltaTime * GetRightVector();	//����Ħ����

	auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto correctionFoce = (tankRoot->GetMass() * correctionAcceleration) / 2;	//�����Ĵ�
	tankRoot->AddForce(correctionFoce);

}

void UT90Track::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	ApplySidiewayForce();
	currentThrottle = 0;	//�ۼ�ϵ������
}
