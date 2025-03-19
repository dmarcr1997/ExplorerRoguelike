// Fill out your copyright notice in the Description page of Project Settings.


#include "ERProjectileBase.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AERProjectileBase::AERProjectileBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;

	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleComp");
	ParticleComp->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
}

// Called when the game starts or when spawned
void AERProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AERProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

