// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ERExplosiveBarrel.generated.h"
class UStaticMeshComponent;
class URadialForceComponent;

UCLASS()
class EXPLORERROGUELIKE_API AERExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AERExplosiveBarrel();

protected:

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* BarrelMesh;

	UPROPERTY(VisibleAnywhere)
	class URadialForceComponent* RadialForce;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	UFUNCTION()
	void FireExplosion(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& HitResult);
};

