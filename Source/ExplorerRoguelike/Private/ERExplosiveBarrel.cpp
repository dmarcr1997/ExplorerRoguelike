// Fill out your copyright notice in the Description page of Project Settings.


#include "ERExplosiveBarrel.h"

#include "PhysicsEngine/RadialForceComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AERExplosiveBarrel::AERExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrelMesh"));
	BarrelMesh->SetSimulatePhysics(true);
	BarrelMesh->SetCollisionProfileName("PhysicsActor");
	RootComponent = BarrelMesh;

	RadialForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForce"));
	RadialForce->SetupAttachment(BarrelMesh);
	RadialForce->SetAutoActivate(false);
	RadialForce->ImpulseStrength = 2000.0f;
	RadialForce->bImpulseVelChange = true;
	RadialForce->ForceStrength = 10.0f;
	RadialForce->Radius = 695.0f;
	RadialForce->AddCollisionChannelToAffect(ECC_WorldDynamic);
	BarrelMesh->OnComponentHit.AddDynamic(this, &AERExplosiveBarrel::FireExplosion);
}

// Called when the game starts or when spawned
void AERExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AERExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AERExplosiveBarrel::FireExplosion(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& HitResult)
{
	RadialForce->FireImpulse();

// 	UE_LOG(LogTemp, Log, TEXT("EXPLODING"));
// 	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s"), *GetNameSafe(OtherActor));
// 	FString CombineString = FString::Printf(TEXT("Hit at location: %s"), *HitResult.ImpactPoint.ToString());
// 	DrawDebugString(GetWorld(), HitResult.ImpactPoint, CombineString, nullptr, FColor::Green, 2.0f, true);
}


