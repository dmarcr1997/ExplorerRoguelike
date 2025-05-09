// Fill out your copyright notice in the Description page of Project Settings.


#include "ERTeleportProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AERTeleportProjectile::AERTeleportProjectile() : AERProjectileBase()
{
	TeleportDelay = 0.2f;
	DetonateDelay = 0.2f;
	ProjectileMovement->InitialSpeed = 6000.0f;
}

void AERTeleportProjectile::Explode_Implementation()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Delayed_Explode);

	UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation(), GetActorRotation());
	ParticleComp->DeactivateImmediate();
	ProjectileMovement->StopMovementImmediately();
	SetActorEnableCollision(false);

	FTimerHandle TimerHandle_DelayedTeleport;
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &AERTeleportProjectile::TeleportInstigator, TeleportDelay);
	
}

void AERTeleportProjectile::TeleportInstigator()
{
	AActor* ActorToTeleport = GetInstigator();
	if (ensure(ActorToTeleport))
	{
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);
	}
}

void AERTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle_Delayed_Explode, this, &AERTeleportProjectile::Explode, DetonateDelay);
}
