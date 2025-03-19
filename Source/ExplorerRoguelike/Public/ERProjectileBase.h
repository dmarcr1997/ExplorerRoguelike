// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ERProjectileBase.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
UCLASS()
class EXPLORERROGUELIKE_API AERProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AERProjectileBase();

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	USphereComponent* SphereComp;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UParticleSystemComponent* ParticleComp;
	
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
