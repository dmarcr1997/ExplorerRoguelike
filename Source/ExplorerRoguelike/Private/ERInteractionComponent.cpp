// Fill out your copyright notice in the Description page of Project Settings.


#include "ERInteractionComponent.h"
#include "DrawDebugHelpers.h"
#include "ERGameplayInterface.h"

// Sets default values for this component's properties
UERInteractionComponent::UERInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	interactionDistance = 1000;
}

void UERInteractionComponent::primaryInteract()
{
	AActor* Owner = GetOwner();
	FVector EyeLocation;
	FRotator EyeRotation;
	
	Owner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	
	FVector EndLocation = EyeLocation + FRotationMatrix(EyeRotation).GetUnitAxis(EAxis::X) * interactionDistance;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
	
	// FHitResult Hit;
	// bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, EndLocation, ObjectQueryParams);

	TArray<FHitResult> Hits;
	float Radius = 30.0f;
	FCollisionShape Shape;
	Shape.SetSphere(30.0f);
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, EndLocation, FQuat::Identity, ObjectQueryParams, Shape);
	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;
	for (FHitResult Hit : Hits)
	{
		DrawDebugSphere(GetWorld(), Hit.Location, Radius, 32, LineColor, false, 2.0f);
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->GetClass()->ImplementsInterface(UERGameplayInterface::StaticClass()))
			{
				APawn* MyPawn = Cast<APawn>(Owner);
				IERGameplayInterface::Execute_Interact(HitActor, MyPawn);
				break;
			}
		}
	}
		
	DrawDebugLine(GetWorld(), EyeLocation, EndLocation, LineColor, false, 2.0f, 0, 2.0f);
}


// Called when the game starts
void UERInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UERInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

