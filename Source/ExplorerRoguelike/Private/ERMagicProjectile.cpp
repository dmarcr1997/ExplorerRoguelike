// Fill out your copyright notice in the Description page of Project Settings.


#include "ERMagicProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AERMagicProjectile::AERMagicProjectile() : AERProjectileBase()
{
	ProjectileMovement->InitialSpeed = 1000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bInitialVelocityInLocalSpace = true;
	ProjectileMovement->ProjectileGravityScale = 0.0f;

}

// Called when the game starts or when spawned
void AERMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AERMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

