// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "T90.generated.h"

UCLASS()
class BATTLETANK_API AT90 : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AT90();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector hitLocation);	//炮管向准心瞄准
	
};
