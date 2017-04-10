// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "T90Track.h"

void UT90Track::SetThrottle(float throttle)
{
	//TODO ���״̬Ҳ��ʩ��������ײ��⣩
	FHitResult hitResult;
	auto startLocation = GetComponentLocation();
	auto endLocation = startLocation + (FVector::UpVector * -100);
	bool hasPickup = GetWorld()->LineTraceSingleByChannel(
		hitResult,
		startLocation,
		endLocation,
		ECollisionChannel::ECC_Visibility);
	if (!hasPickup) return;

	//������ֵת��Ϊ������
	auto forceApplied = GetForwardVector() * throttle * maxTrackDrivingForce;
	//���̹�˱���
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//���������Ĵ�������
	tankRoot->AddForceAtLocation(forceApplied, GetComponentLocation());
}
