// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FPLamp.h"
#include "Kismet/GameplayStatics.h"



void AFPLamp::BeginPlay()
{
	Super::BeginPlay();
	// Get Material Instance to edit. 
	CodeMaterialInst = MeshComp->CreateDynamicMaterialInstance(0);

	MeshComp->OnComponentBeginOverlap.AddDynamic(this, &AFPLamp::OverlapBegin);
}

void AFPLamp::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ToggleLamp();
}

void AFPLamp::ToggleLamp()
{
	// toggle isOn. 
	IsOn = !IsOn;

	// Toggle emissive strength. 
	CodeMaterialInst->SetScalarParameterValue("EmissiveStrength", IsOn ? 20.0f : 0.0f);
	
	OnLightSwitchedOnDelegate.Broadcast();
		
}

void AFPLamp::Interact_Implementation()
{
	ToggleLamp();
}

bool AFPLamp::CanInteract_Implementation()
{
	return false;
}

