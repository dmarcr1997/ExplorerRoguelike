// Fill out your copyright notice in the Description page of Project Settings.


#include "ERAttributeComponent.h"

// Sets default values for this component's properties
UERAttributeComponent::UERAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	Health = MaxHealth;
}

bool UERAttributeComponent::isAlive() const
{
	return Health > 0;
}

bool UERAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;
	Health = FMath::Clamp(Health, 0, MaxHealth);
	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);
	
	return true;
}

