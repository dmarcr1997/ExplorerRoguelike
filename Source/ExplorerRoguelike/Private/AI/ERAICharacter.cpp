// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ERAICharacter.h"

// Sets default values
AERAICharacter::AERAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AERAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AERAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


