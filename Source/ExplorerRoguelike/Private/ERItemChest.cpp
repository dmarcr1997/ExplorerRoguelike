// Fill out your copyright notice in the Description page of Project Settings.


#include "ERItemChest.h"

void AERItemChest::Interact_Implementation(APawn* InstigatingPawn)
{
	LidMesh->SetRelativeRotation(FRotator(targetPitch, 0, 0));
}

// Sets default values
AERItemChest::AERItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;
	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);

	targetPitch = 110;
}

// Called when the game starts or when spawned
void AERItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AERItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

