// Fill out your copyright notice in the Description page of Project Settings.


#include "ERMagicProjectile.h"

#include "ERAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AERMagicProjectile::AERMagicProjectile() : AERProjectileBase()
{
}

void AERMagicProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, GetActorLocation(), GetActorRotation());
		UERAttributeComponent* AttributeComp = Cast<UERAttributeComponent>(OtherActor->GetComponentByClass(UERAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(DamageAmount);
		}
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
		Destroy();
	}
}

