// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FPLamp.h"
#include "Kismet/GameplayStatics.h"

void AFPLamp::BeginPlay()
{
	Super::BeginPlay();
	// Get Material Instance to edit. 
	CodeMaterialInst = MeshComp->CreateDynamicMaterialInstance(0);
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

