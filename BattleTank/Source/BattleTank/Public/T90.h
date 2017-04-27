// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "T90.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FT90Delegate);

UCLASS()
class BATTLETANK_API AT90 : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int initialHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int currentHealth = initialHealth;

public:
	FT90Delegate OnDeath;
	
	AT90();
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;		//当前血量比
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
