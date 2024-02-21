// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/FPMeshActorBase.h"
#include "Interfaces/Interact.h"
#include "FPBomb.generated.h"

/**
 * 
 */
class UNiagaraComponent;
class AFPLamp; 
class UNiagaraSystem;
UCLASS()
class FIRSTPROJECT_API AFPBomb : public AFPMeshActorBase, public IInteract
{
	GENERATED_BODY()

public:

	AFPBomb();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StartIgnite();

	virtual void Interact_Implementation() override;

	virtual bool CanInteract_Implementation() override;

protected: 
	
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ignition", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMaterialInstanceDynamic> CodeMaterialInst;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actor Reference", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AFPLamp> LampRefCpp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Particle", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraComponent> SparkEffectComponent;
	
	UPROPERTY(EditAnywhere, Category = "Explosion", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraSystem> ExplosionEffect;

	// - AUDIO - // 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> ExplosionSound;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USoundBase> FuseSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ignition", meta = (AllowPrivateAccess = "true"))
	float IgniteDuration = 2.0f;

	bool HasBeenIgnited = false;	

	UFUNCTION(BlueprintCallable)
	void Explode();	

};
