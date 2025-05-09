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
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
};
