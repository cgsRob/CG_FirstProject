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
	CodeIsOn = !CodeIsOn;

	// Toggle emissive strength. 
	CodeMaterialInst->SetScalarParameterValue("EmissiveStrength", CodeIsOn ? 20.0f : 0.0f);

	if (CodeDoorRef)
	{
		// Open door.
		if (UKismetSystemLibrary::DoesImplementInterface(CodeDoorRef, UInteract::StaticClass()))
		{
			IInteract::Execute_Interact(CodeDoorRef);
		}
		// Remove Ref
		CodeDoorRef = nullptr;
	}

	// Find all potential bombs.	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UInteract::StaticClass(), FoundActors);

	for (auto FoundActor : FoundActors)
	{
		if (UKismetSystemLibrary::DoesImplementInterface(FoundActor, UInteract::StaticClass()))
		{
			if (IInteract::Execute_CanInteract(FoundActor))
			{
				IInteract::Execute_Interact(FoundActor);
			}
		}
	}	
}

void AFPLamp::Interact_Implementation()
{
	ToggleLamp();
}

bool AFPLamp::CanInteract_Implementation()
{
	return false;
}

