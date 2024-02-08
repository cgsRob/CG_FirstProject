// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/FPMeshActorBase.h"
#include "FPLamp.generated.h"


class AFPBomb; 
class AFPDoor;
UCLASS()
class FIRSTPROJECT_API AFPLamp : public AFPMeshActorBase
{
	GENERATED_BODY()
	
public:

	void ToggleLamp();

protected:

	virtual void BeginPlay() override;

	TObjectPtr<UMaterialInstanceDynamic> CodeMaterialInst;

	// UPROPERRTY to expose to editor. 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "References")
	TObjectPtr<AFPDoor> CodeDoorRef;

private:
	// Example of not exposing to force getting the reference in code.
	TObjectPtr<AFPBomb> CodeBombRef;

	bool CodeIsOn = false;

};
