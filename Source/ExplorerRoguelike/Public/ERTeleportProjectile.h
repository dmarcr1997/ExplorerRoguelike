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
	
	virtual void BeginPlay() override;

	FTimerHandle TimerHandle_Explode;
	void Explode_TimeElapsed();

	UFUNCTION(BlueprintCallable)
	void Explode();

	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
};
