// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 350.0f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArm);
	CameraComponent->FieldOfView = 90.0f;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	isScoped = false;
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isScoped)
	{
		if (CameraComponent->FieldOfView > 45.0f)
		{
			CameraComponent->FieldOfView = (FMath::FInterpTo(CameraComponent->FieldOfView, 45.0f, DeltaTime, 10.0f));
		}
	}
	else
	{
		if (CameraComponent->FieldOfView < 90.0f)
		{
			CameraComponent->FieldOfView = (FMath::FInterpTo(CameraComponent->FieldOfView, 90.0f, DeltaTime, 10.0f));
		}
	}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyCharacter::AimDownSight(bool ShouldADS)
{
	if ((ShouldADS == true) && (GetCharacterMovement()->IsFalling() == false))
	{
		isScoped = true;
	}
	else
	{
		isScoped = false;
	}
}

bool AMyCharacter::ReturnAimDownSightStatus()
{
	return isScoped;
}

