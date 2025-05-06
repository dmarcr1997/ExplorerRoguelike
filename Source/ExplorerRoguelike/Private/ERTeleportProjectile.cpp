// Fill out your copyright notice in the Description page of Project Settings.


#include "ERTeleportProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AERTeleportProjectile::AERTeleportProjectile() : AERProjectileBase()
{
	ProjectileMovement->InitialSpeed = 1000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bInitialVelocityInLocalSpace = true;
	ProjectileMovement->ProjectileGravityScale = 0.5f;
	SphereComp->OnComponentHit.AddDynamic(this, &AERTeleportProjectile::OnActorHit);
	SphereComp->SetNotifyRigidBodyCollision(true);
}

void AERTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle_Explode, this, &AERTeleportProjectile::Explode_TimeElapsed, 1.0f);
}

void AERTeleportProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, GetActorLocation(), GetActorRotation());
		GetWorldTimerManager().ClearTimer(TimerHandle_Explode);
		Explode();
	}
}

void AERTeleportProjectile::Explode_TimeElapsed()
{
	Explode();
}


void AERTeleportProjectile::Explode()
{
	FVector SafeLocation = GetActorLocation() + FVector(0, 0, 50.0f);
	GetInstigator()->TeleportTo(SafeLocation,GetInstigator()->GetActorRotation());
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, GetActorLocation(), GetActorRotation());
	Destroy();
}
