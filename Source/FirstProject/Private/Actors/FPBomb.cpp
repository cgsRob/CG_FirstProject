// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/FPBomb.h"
#include "Actors/FPLamp.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"

AFPBomb::AFPBomb()
{
	SparkEffectComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Dust Particle"));
	SparkEffectComponent->SetupAttachment(GetRootComponent());
}

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
	AudioComponent->Sound = FuseSound;
	AudioComponent->Play();
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
	if (ExplosionEffect)
	{		
		const FVector ActorLocation = GetActorLocation(); 
		const FVector SpawnLocation = FVector(ActorLocation.X, ActorLocation.Y, ActorLocation.Z + MeshComp->Bounds.BoxExtent.Z / 2);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionEffect, SpawnLocation);
	}
	if (ExplosionSound)
	{
		AudioComponent->Stop();
		UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
	}

	// Destroy
	Destroy();
}
