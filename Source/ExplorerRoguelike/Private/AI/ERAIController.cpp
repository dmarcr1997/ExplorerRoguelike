// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ERAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AERAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);

	APawn* MyPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (MyPawn)
	{
		GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), MyPawn);
	}
}
