// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ERGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "ERItemChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class EXPLORERROGUELIKE_API AERItemChest : public AActor, public IERGameplayInterface
{
	GENERATED_BODY()
	void Interact_Implementation(APawn* InstigatingPawn);
public:	
	// Sets default values for this actor's properties
	AERItemChest();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UStaticMeshComponent* LidMesh;

	UPROPERTY(EditAnywhere)
	float targetPitch;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
