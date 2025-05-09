// Fill out your copyright notice in the Description page of Project Settings.


#include "ERCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ERAttributeComponent.h"
#include "ERInteractionComponent.h"
#include "ERProjectileBase.h"

// Sets default values
AERCharacter::AERCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");

	// Setup Attachments
	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp->SetupAttachment(SpringArmComp);

	// Character Movement setup
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, RotationRate, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;


	// Spring Arm Config
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 15.0f;

	// Camera Config
	CameraComp->bUsePawnControlRotation = false;

	//Interaction component
	InteractionComp = CreateDefaultSubobject<UERInteractionComponent>("InteractionComponent");

	//Attribute component
	AttributeComp = CreateDefaultSubobject<UERAttributeComponent>("AttributeComponent");
}

void AERCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComp->OnHealthChanged.AddDynamic(this, &AERCharacter::OnHealthChange);
}

// Called when the game starts or when spawned
void AERCharacter::BeginPlay()
{
	Super::BeginPlay();

		
	// Input setup
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
}

void AERCharacter::OnHealthChange(AActor* InstigatorActor, UERAttributeComponent* OwningComp, float NewHealth,
	float Delta)
{
	if (NewHealth <= 0.0f && Delta <= 0.0f)
	{
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		DisableInput(PlayerController);
	}
}

void AERCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRot(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X); //Forward Vector
		const FVector RightDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y); //Right Vector
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AERCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X * LookSensitivity);
		AddControllerPitchInput(LookAxisVector.Y * LookSensitivity);
	}
}

void AERCharacter::StartJump()
{
	Jump();
}

void AERCharacter::StopJump()
{
	StopJumping();
}

void AERCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AERCharacter::PrimaryAttack_TimeElapsed, 0.2f);
}

void AERCharacter::SecondaryAttack()
{
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(TimerHandle_SecondaryAttack, this, &AERCharacter::SecondaryAttack_TimeElapsed, 0.2f);
}

void AERCharacter::Teleport()
{
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(TimerHandle_Teleport, this, &AERCharacter::Teleport_TimeElapsed, 0.2f);
}

void AERCharacter::PrimaryInteract()
{
	InteractionComp->primaryInteract();
}

void AERCharacter::SpawnProjectile(TSubclassOf<AActor> ProjectileType)
{
	if (ensure(ProjectileType)){
		FVector TraceStart = CameraComp->GetComponentLocation();
		FVector TraceEnd = TraceStart + GetControlRotation().Vector() * 5000;
		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
		FHitResult HitResult;

		FCollisionShape Shape;
		Shape.SetSphere(20.0f);
		
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		
		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
		ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
		ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
		
		if (GetWorld()->SweepSingleByObjectType(HitResult, TraceStart, TraceEnd, FQuat::Identity, ObjectQueryParams, Shape, Params))
		{
			TraceEnd = HitResult.ImpactPoint;
		}
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		FRotator ProjectileRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();
		FTransform SpawnTM =  FTransform(ProjectileRotation, HandLocation);
		GetWorld()->SpawnActor<AActor>(ProjectileType, SpawnTM, SpawnParams);
	}
}

void AERCharacter::PrimaryAttack_TimeElapsed()
{
	SpawnProjectile(ProjectileClass);
}

void AERCharacter::SecondaryAttack_TimeElapsed()
{
	SpawnProjectile(SecondaryProjectileClass);
}

void AERCharacter::Teleport_TimeElapsed()
{
	SpawnProjectile(TeleportProjectileClass);
}


// Called every frame
void AERCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AERCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AERCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AERCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AERCharacter::StartJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AERCharacter::StopJump);
		EnhancedInputComponent->BindAction(PrimaryAttackAction, ETriggerEvent::Started, this, &AERCharacter::PrimaryAttack);
		EnhancedInputComponent->BindAction(SecondaryAttackAction, ETriggerEvent::Started, this, &AERCharacter::SecondaryAttack);
		
		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Started, this, &AERCharacter::PrimaryInteract);
		EnhancedInputComponent->BindAction(TeleportAction, ETriggerEvent::Started, this, &AERCharacter::Teleport);
	}

}

