#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera SAC"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->TargetArmLength = 450.0f;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraSpringArm);

	//FPSSkeletalSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	//FPSSkeletalSpringArm->SetupAttachment(RootComponent);
	//FPSSkeletalSpringArm->TargetArmLength = 0.0f;
	//FPSSkeletalComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPS Mesh"));
	//FPSSkeletalComponent->SetupAttachment(RootComponent);
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMyCharacter::Fire()
{
}
