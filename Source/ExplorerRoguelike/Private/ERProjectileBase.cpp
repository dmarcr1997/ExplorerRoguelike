// Fill out your copyright notice in the Description page of Project Settings.


#include "ERProjectileBase.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "UObject/FastReferenceCollector.h"

// Sets default values
AERProjectileBase::AERProjectileBase()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentHit.AddDynamic(this, &AERProjectileBase::OnActorHit);
	RootComponent = SphereComp;

	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleComp");
	ParticleComp->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bInitialVelocityInLocalSpace = true;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->InitialSpeed = 8000;
}

void AERProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

void AERProjectileBase::Explode_Implementation()
{
	if (ensure(!IsPendingKillPending()))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation(), GetActorRotation());
		Destroy();
	}
}

void AERProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (GetInstigator())
	{
		SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	}
}
