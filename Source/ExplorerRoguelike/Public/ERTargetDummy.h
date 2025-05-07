// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ERAttributeComponent.h"
#include "GameFramework/Actor.h"
#include "ERTargetDummy.generated.h"

class UERAttributeComponent;

UCLASS()
class EXPLORERROGUELIKE_API AERTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AERTargetDummy();

protected:
	UPROPERTY(VisibleAnywhere)
	UERAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	UFUNCTION()
	void OnHealthChange(AActor* InstigatorActor, UERAttributeComponent* OwningComp, float NewHealth, float Delta);
};
