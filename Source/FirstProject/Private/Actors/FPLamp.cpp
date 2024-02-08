// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FPLamp.h"
#include "Actors/FPBomb.h"
#include "Actors/FPDoor.h"
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
	CodeIsOn = !CodeIsOn;

	// Toggle emissive strength. 
	CodeMaterialInst->SetScalarParameterValue("EmissiveStrength", CodeIsOn ? 20.0f : 0.0f);

	if (CodeDoorRef)
	{
		// Open door.
		CodeDoorRef->OpenDoor();
		// Remove Ref
		CodeDoorRef = nullptr;
	}

	// Find a bomb. 
	CodeBombRef = Cast<AFPBomb>(UGameplayStatics::GetActorOfClass(GetWorld(), AFPBomb::StaticClass()));

	if (CodeBombRef && !CodeBombRef->HasBeenIgnited)
	{
		// ignite bomb. 
		CodeBombRef->StartIgnite();
	}
}

