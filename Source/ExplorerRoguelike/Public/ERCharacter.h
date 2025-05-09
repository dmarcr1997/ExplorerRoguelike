// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HAL/MallocBinned2.h"
#include "ERCharacter.generated.h"


// FORWARD DECS
class AERProjectileBase;
class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UERInteractionComponent;
class UERAttributeComponent;
class UAnimMontage;

UCLASS()
class EXPLORERROGUELIKE_API AERCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AERCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// INPUT ACTIONS
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* PrimaryAttackAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* SecondaryAttackAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* TeleportAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* InteractionAction;

	// PARAMS
	UPROPERTY(EditAnywhere, Category="Movement")
	float MovementSpeed = 600.0f;

	UPROPERTY(EditAnywhere, Category="Movement")
	float RotationRate = 500.0f;

	UPROPERTY(EditAnywhere, Category="Camera")
	float LookSensitivity = 1.0f;

	UPROPERTY(EditAnywhere, Category="Combat")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category="Combat")
	TSubclassOf<AActor> SecondaryProjectileClass;

	UPROPERTY(EditAnywhere, Category="Combat")
	TSubclassOf<AActor> TeleportProjectileClass;

	
	UPROPERTY(EditAnywhere, Category="Components")
	UERInteractionComponent* InteractionComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	UERAttributeComponent* AttributeComp;

	// ANIMATION PARAMS
	UPROPERTY(EditAnywhere, Category="Attack")
	UAnimMontage* AttackAnim;

	UFUNCTION()
	void OnHealthChange(AActor* InstigatorActor, UERAttributeComponent* OwningComp, float NewHealth, float Delta);

	virtual void PostInitializeComponents() override;
private:
	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerHandle TimerHandle_SecondaryAttack;
	FTimerHandle TimerHandle_Teleport;
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartJump();
	void StopJump();
	void PrimaryAttack();
	void SecondaryAttack();
	void Teleport();
	void PrimaryInteract();
	void SpawnProjectile(TSubclassOf<AActor> ProjectileType);
	void PrimaryAttack_TimeElapsed();
	void SecondaryAttack_TimeElapsed();
	void Teleport_TimeElapsed();
};
