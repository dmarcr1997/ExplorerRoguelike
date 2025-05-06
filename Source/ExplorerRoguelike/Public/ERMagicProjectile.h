// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ERProjectileBase.h"
#include "GameFramework/Actor.h"
#include "ERMagicProjectile.generated.h"

UCLASS()
class EXPLORERROGUELIKE_API AERMagicProjectile : public AERProjectileBase
{
	GENERATED_BODY()
	
public:	
	AERMagicProjectile();

protected:
	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
