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
#include "MyCharacter.h"

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
	if (Cast<AMyCharacter>(SourceActor))
	{
		AAIController* ZombieAIController = ReturnZombieAIController();
		if (ZombieAIController != nullptr)
		{
			ZombieAIController->GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), SourceActor);
		}
	}
	else
	{
		AAIController* ZombieAIController = ReturnZombieAIController();
		if (ZombieAIController != nullptr)
		{
			ZombieAIController->GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), nullptr);
		}
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
	Destroy();
}

AAIController* AZombieCharacter::ReturnZombieAIController()
{
	auto* ZombieControllers = this->GetController();
	auto ZombieAIController = Cast<AAIController>(ZombieControllers);
	if (ZombieAIController != nullptr)
	{
		return ZombieAIController;
	}
	else
	{
		return nullptr;
	}
}
