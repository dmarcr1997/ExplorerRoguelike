// Fill out your copyright notice in the Description page of Project Settings.


#include "ERAttributeComponent.h"

// Sets default values for this component's properties
UERAttributeComponent::UERAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	Health = 100;
}

bool UERAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);
	
	return true;
}

