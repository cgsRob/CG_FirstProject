// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FPBomb.h"

void AFPBomb::StartIgnite()
{
	// Hint at ignition starting
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, TEXT("FzzzzZZZzz!"));

	// Call Explode after time.
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AFPBomb::Explode, 2.0f, false);

	HasBeenIgnited = true;
}

void AFPBomb::Explode()
{
	// Hint at explosion.
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, TEXT("boom!"));

	// Destroy
	Destroy();
}
