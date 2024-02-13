// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/FPBomb.h"
#include "Actors/FPLamp.h"

void AFPBomb::BeginPlay()
{
	Super::BeginPlay();

	if (LampRefCpp)
	{
		LampRefCpp->OnLightSwitchedOnDelegate.AddUniqueDynamic(this, &AFPBomb::StartIgnite);
	}
}

void AFPBomb::StartIgnite()
{
	if (HasBeenIgnited)
		return; 

	// Hint at ignition starting
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, TEXT("FzzzzZZZzz!"));

	// Call Explode after time.
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AFPBomb::Explode, 2.0f, false);

	HasBeenIgnited = true;
}

void AFPBomb::Interact_Implementation()
{
	StartIgnite();
}

bool AFPBomb::CanInteract_Implementation()
{
	return !HasBeenIgnited;
}

void AFPBomb::Explode()
{
	// Hint at explosion.
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, TEXT("boom!"));

	// Destroy
	Destroy();
}
