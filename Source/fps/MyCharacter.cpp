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

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 350.0f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArm);
	CameraComponent->FieldOfView = 90.0f;
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	isScoped = false;
	isSprinting = false;
	
}

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
}

void AMyCharacter::Fire()
{
	if (CanFire())
	{
		//UNiagaraComponent* FireVFX = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this->GetWorld(), MuzzleFlash_VFX, FireEffectMuzzleLocation);
		//PlayParticleEffect();
		FVector StartVector = CameraComponent->GetComponentLocation();
		FVector EndVector = StartVector + (CameraComponent->GetForwardVector() * 2000.0f);

		isHit = GetWorld()->LineTraceSingleByChannel(HitRes, StartVector, EndVector, ECollisionChannel::ECC_Visibility);
		if (isHit)
		{
			AActor* VictimActor = HitRes.GetActor();
			USkeletalMeshComponent* VictimSkeletalMeshComponent = VictimActor->GetComponentByClass<USkeletalMeshComponent>();
			if (VictimSkeletalMeshComponent != nullptr)
			{
				if (VictimSkeletalMeshComponent->ComponentHasTag(TEXT("Zombie")))
				{
					TSubclassOf<UDamageType> GunDamageType = UDamageType::StaticClass();
					AController* PlayerInstigator = GetInstigator()->GetController();
					UGameplayStatics::ApplyDamage(VictimActor, 25.0f, PlayerInstigator, this, GunDamageType);
				}
			}
		}

		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this->GetWorld(), 0);
		ACharacter* PlayerCharacter = PlayerController->GetCharacter();
		UAnimInstance* PlayerAnimInstance = PlayerCharacter->GetMesh()->GetAnimInstance();
		if (RifleShootingAnimMontage != nullptr && PlayerAnimInstance != nullptr)
		{
			PlayerAnimInstance->Montage_Play(RifleShootingAnimMontage);
		}
		else
		{
		}
	}
}

void AMyCharacter::Reload()
{
}

