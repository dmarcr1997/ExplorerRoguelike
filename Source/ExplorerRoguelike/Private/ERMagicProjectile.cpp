// Fill out your copyright notice in the Description page of Project Settings.


#include "ERMagicProjectile.h"

#include "ERAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AERMagicProjectile::AERMagicProjectile() : AERProjectileBase()
{
	ProjectileMovement->InitialSpeed = 1000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bInitialVelocityInLocalSpace = true;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	SphereComp->OnComponentHit.AddDynamic(this, &AERMagicProjectile::OnActorHit);
	SphereComp->SetNotifyRigidBodyCollision(true);
}

void AERMagicProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		UE_LOG(LogTemp, Display, TEXT("OnActorHit"));
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, GetActorLocation(), GetActorRotation());
		UERAttributeComponent* AttributeComp = Cast<UERAttributeComponent>(OtherActor->GetComponentByClass(UERAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(-20);
		}
		UE_LOG(LogTemp, Display, TEXT("DESTROY"));
		Destroy();
	}
	UE_LOG(LogTemp, Display, TEXT("OnActorHit Didn't do it.."));
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

