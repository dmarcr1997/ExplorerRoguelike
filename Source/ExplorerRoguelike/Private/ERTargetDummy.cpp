// Fill out your copyright notice in the Description page of Project Settings.


#include "ERTargetDummy.h"

// Sets default values
AERTargetDummy::AERTargetDummy()
{
 	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	AttributeComp = CreateDefaultSubobject<UERAttributeComponent>("AttributeComp");
	AttributeComp->OnHealthChanged.AddDynamic(this, &AERTargetDummy::OnHealthChange);

}

void AERTargetDummy::OnHealthChange(AActor* InstigatorActor, UERAttributeComponent* OwningComp, float NewHealth,
	float Delta)
{
	if (Delta < 0.0f)
	{
		MeshComp->SetScalarParameterValueOnMaterials(TEXT("TimeToHit"), GetWorld()->TimeSeconds);
	}
}


