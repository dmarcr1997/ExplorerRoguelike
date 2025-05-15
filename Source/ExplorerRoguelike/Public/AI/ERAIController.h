// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ERAIController.generated.h"

/**
 * 
 */

class UBehaviorTree;
UCLASS()
class EXPLORERROGUELIKE_API AERAIController : public AAIController
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTree;
	
	
};
