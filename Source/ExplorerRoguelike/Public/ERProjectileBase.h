// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ERProjectileBase.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class UParticleSystem;
class UAudioComponent;
class USoundBase;
UCLASS(Abstract)
class EXPLORERROGUELIKE_API AERProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AERProjectileBase();

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Effects")
	UParticleSystem* HitParticle;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Effects")
	USoundBase* ImpactSound;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Components")
	USphereComponent* SphereComp;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Components")
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Components")
	UParticleSystemComponent* ParticleComp;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Components")
	UAudioComponent* AudioComp;


	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode();

	virtual void PostInitializeComponents() override;
};
