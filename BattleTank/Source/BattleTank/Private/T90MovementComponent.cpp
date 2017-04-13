// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "T90Track.h"
#include "T90MovementComponent.h"

void UT90MovementComponent::Initialize(UT90Track *leftTrackToSet, UT90Track *rightTrackToSet)
{
	if (!leftTrackToSet || !rightTrackToSet) return;
	leftTrack = leftTrackToSet;
	rightTrack = rightTrackToSet;
}

void UT90MovementComponent::IntendMoveForward(float throttle)
{
	leftTrack->SetThrottle(throttle);
	rightTrack->SetThrottle(throttle);
}

void UT90MovementComponent::IntendTurnRight(float throttle)
{
	leftTrack->SetThrottle(throttle);
	rightTrack->SetThrottle(-throttle);
}

void UT90MovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//不需要调用父类实现
	auto tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto aiForwardIntention = MoveVelocity.GetSafeNormal();
	//点积获取移动量
	auto forwardThrow = FVector::DotProduct(tankForward, aiForwardIntention);
	IntendMoveForward(forwardThrow);	
	//叉积的Z值映射旋转量
	auto rightThrow = FVector::CrossProduct(aiForwardIntention, tankForward).Z;
	IntendTurnRight(rightThrow);
}
