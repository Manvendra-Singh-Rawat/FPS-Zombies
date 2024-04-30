#include "ZombieCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AISenseConfig_Sight.h"
#include "AIController.h"
#include <Actions/PawnActionsComponent.h>
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"
#include "Components/WidgetComponent.h"

AZombieCharacter::AZombieCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sense Config"));
	AIPerceptionComponent->ConfigureSense(*SightConfig);
	SightConfig->SightRadius = 3000.0f;
	SightConfig->LoseSightRadius = 3500.0f;
	SightConfig->PeripheralVisionAngleDegrees = 60.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AZombieCharacter::isDetectedPlayer);

	UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, SightConfig->GetSenseImplementation(), UGameplayStatics::GetPlayerPawn(this, 0));

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Comp"));

	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Widget Comp"));
	HealthBarWidget->SetupAttachment(RootComponent);
}

void AZombieCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AZombieCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AZombieCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AZombieCharacter::isDetectedPlayer(AActor* SourceActor, FAIStimulus Stimulus)
{
	ACharacter* PlayerCharacterReference = UGameplayStatics::GetPlayerCharacter(this->GetWorld(), 0);
	if (PlayerCharacterReference != nullptr)
	{
		AActor* PlayerActorReference = Cast<AActor>(PlayerCharacterReference);
		if (SourceActor == PlayerActorReference)
		{
			AController* ZombieController = this->GetController();
			if (ZombieController != nullptr)
			{
				AAIController* ZombieAIController = Cast<AAIController>(ZombieController);
				ZombieAIController->GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), SourceActor);
			}
		}
		else
		{
			AController* ZombieController = this->GetController();
			if (ZombieController != nullptr)
			{
				AAIController* ZombieAIController = Cast<AAIController>(ZombieController);
				ZombieAIController->GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), nullptr);
			}
		}
	}
	else
	{
		return;
	}
}

void AZombieCharacter::PlayDeadPart()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Zombie Character died"));
	auto asdf = GetComponentByClass<USkeletalMeshComponent>();
	if (asdf != nullptr)
	{
		asdf->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);

		// PLAY VFX AND SFX
	}

	// TODO
	// DESTROY THE AACTOR AFTER 5 SECONDS
}
