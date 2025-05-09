// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ERProjectileBase.h"
#include "ERTeleportProjectile.generated.h"
class UParticleSystemComponent;
/**
 * 
 */
UCLASS()
class EXPLORERROGUELIKE_API AERTeleportProjectile : public AERProjectileBase
{
	GENERATED_BODY()
public:
	AERTeleportProjectile();
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Teleport")
	float TeleportDelay;

	UPROPERTY(EditDefaultsOnly, Category="Teleport")
	float DetonateDelay;
	
	FTimerHandle TimerHandle_Delayed_Explode;	

	virtual void Explode_Implementation() override;

	void TeleportInstigator();
	
	virtual void BeginPlay() override;
	
};
