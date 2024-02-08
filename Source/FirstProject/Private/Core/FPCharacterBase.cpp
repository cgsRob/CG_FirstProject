// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/FPCharacterBase.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Actors/FPLamp.h"

// Sets default values
AFPCharacterBase::AFPCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void AFPCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPCharacterBase::Move(const FInputActionValue& Value)
{
	// Initial version getting a 1D float from the Value. Kept for reference. 
	//const float Move = Value.Get<float>();

	// New 2D Vector returned from Value to drive forward, back, left, right. 
	FVector2D MoveVector = Value.Get<FVector2D>();

	// Get the length of a vector and check it != 0, ensure one of the directions are pressed. 
	if (MoveVector.Length() != 0.0f)
	{
		// Move Along an axis. Input Action needs Swizzle for Y. 
		AddMovementInput(GetActorForwardVector() * MoveVector.X);
		AddMovementInput(GetActorRightVector() * MoveVector.Y);
	}
}

void AFPCharacterBase::Look(const FInputActionValue& Value)
{
	// New 2D Vector returned from Value to drive forward, back, left, right. 
	FVector2D LookVector = Value.Get<FVector2D>();

	// Get the length of a vector and check it != 0, ensure one of the directions are pressed. 
	if (LookVector.Length() != 0.0f)
	{
		// Add rotation offset along an axis (Yaw, Pitch, Roll). Input Action needs Swizzle for Y. 
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
}

void AFPCharacterBase::Interact()
{
	// Varaibles for trace. 
	FHitResult OutHit;
	FVector Start = Camera->GetComponentLocation();

	FVector Forward = Camera->GetForwardVector();
	FVector End = ((Forward * 1000.0f) + Start);

	FCollisionQueryParams CollisionParams;

	// Visualise Trace.
	DrawDebugLine(GetWorld(), Start, End, FColor::Orange, false, 1, 0, 1);

	if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams))
	{

		if (AFPLamp* CurrentLamp = Cast<AFPLamp>(OutHit.GetActor()))
		{
			CurrentLamp->ToggleLamp();
		}
	}
}

// Called every frame
void AFPCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFPCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveActions, ETriggerEvent::Triggered, this, &AFPCharacterBase::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFPCharacterBase::Look);

		// Note that the Jump function is not being called through AFPCharacterBase, it's making use of the base ACharacter class Jump/StopJump functionality. 
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AFPCharacterBase::Interact);
	}
}

