// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "T90.h"

// Sets default values
AT90::AT90()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AT90::BeginPlay()
{
	Super::BeginPlay();
	currentHealth = initialHealth;
}

float AT90::GetHealthPercent() const
{
	return (float)currentHealth/initialHealth;
}

float AT90::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int damage = FPlatformMath::RoundToInt(DamageAmount);
	int damageToApply = FMath::Clamp(damage, 0, currentHealth);

	currentHealth -= damageToApply;
	if (currentHealth <= 0)
	{
		OnDeath.Broadcast();
	}

	return damageToApply;
}
