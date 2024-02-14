// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/FPBomb.h"
#include "Actors/FPLamp.h"

void AFPBomb::BeginPlay()
{
	Super::BeginPlay();

	// Get Material Instance to edit. 
	CodeMaterialInst = MeshComp->CreateDynamicMaterialInstance(0);

	if (LampRefCpp)
	{
		LampRefCpp->OnLightSwitchedOnDelegate.AddUniqueDynamic(this, &AFPBomb::Interact);
	}
}

void AFPBomb::StartIgnite_Implementation()
{
	HasBeenIgnited = true;
}

void AFPBomb::Interact_Implementation()
{
	if (HasBeenIgnited)
		return;

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
