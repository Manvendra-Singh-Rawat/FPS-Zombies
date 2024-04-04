// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"

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
	isSprinting = false;
	
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
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		isScoped = true;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 400.0f;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		isScoped = false;
	}
}

bool AMyCharacter::ReturnAimDownSightStatus()
{
	return isScoped;
}

void AMyCharacter::ToggleSprint()
{
	if (isScoped == false)
	{
		if (isSprinting)
		{
			GetCharacterMovement()->MaxWalkSpeed = 400.0f;
		}
		else
		{
			GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		}
		isSprinting = !isSprinting;
	}
}

bool AMyCharacter::CanFire()
{
	if (isScoped == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void AMyCharacter::StartFire()
{
	GetWorldTimerManager().SetTimer(FiringTimerhandler, this, &AMyCharacter::Fire, 0.1f, true, 0.0f);
}
void AMyCharacter::StopFire()
{
	GetWorldTimerManager().ClearTimer(FiringTimerhandler);
	//UNiagaraComponent* FireVFX = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this->GetWorld(), FireEffectMuzzle, FireEffectMuzzleLocation);
}

void AMyCharacter::Fire()
{
	if (CanFire())
	{
		FVector StartVector = CameraComponent->GetComponentLocation();
		FVector EndVector = StartVector + (CameraComponent->GetForwardVector() * 2000.0f);

		isHit = GetWorld()->LineTraceSingleByChannel(HitRes, StartVector, EndVector, ECollisionChannel::ECC_Visibility);
		if (isHit)
		{
			DrawDebugBox(this->GetWorld(), HitRes.ImpactPoint, FVector(1.5f, 1.5f, 1.5f), FColor::Yellow, false, 0.5f, 0U, 1.0f);
		}

		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this->GetWorld(), 0);
		ACharacter* PlayerCharacter = PlayerController->GetCharacter();
		UAnimInstance* PlayerAnimInstance = PlayerCharacter->GetMesh()->GetAnimInstance();
		if (RifleShootingAnimMontage != nullptr && PlayerAnimInstance != nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Working"));
			PlayerAnimInstance->Montage_Play(RifleShootingAnimMontage);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Not working"));
		}
	}
}

void AMyCharacter::Reload()
{
}

