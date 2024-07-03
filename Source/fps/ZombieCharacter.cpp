#include "ZombieCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AISenseConfig_Sight.h"
#include "AIController.h"
#include "Enemy_AIController.h"
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
	auto asdf = Cast<AMyCharacter>(SourceActor);
	if (asdf != nullptr)
	{
		if (asdf->isPlayerDead != true)
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
	USkeletalMeshComponent* SkeletalMeshComponent = GetComponentByClass<USkeletalMeshComponent>();
	if (SkeletalMeshComponent != nullptr)
	{
		SkeletalMeshComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);

		// PLAY VFX AND SFX
	}
	auto asdf = Cast<AEnemy_AIController>(ReturnZombieAIController());
	if (asdf != nullptr)
	{
		asdf->KillBehaviorTree();
	}
	// TODO
	// DESTROY THE AACTOR AFTER 5 SECONDS
	//Destroy();
	DeathRagdall();
	GetWorldTimerManager().SetTimer(ZombieDeathDespawnHandler, this, &AZombieCharacter::Death, 0.1f, false, 3.0f);
}

AAIController* AZombieCharacter::ReturnZombieAIController()
{
	AController* ZombieControllers = this->GetController();
	AAIController* ZombieAIController = Cast<AAIController>(ZombieControllers);
	if (ZombieAIController != nullptr)
	{
		return ZombieAIController;
	}
	else
	{
		return nullptr;
	}
}

void AZombieCharacter::AttackPlayer()
{
	if (ZombieAttackAnimMontage.Num() >= 1 && ZombieAnimationInstance != nullptr)
	{
		ZombieAnimationInstance->Montage_Play(ZombieAttackAnimMontage[FMath::RandRange(0, 3)]);
	}
}

void AZombieCharacter::ApplyDamageToPlayer()
{
	UGameplayStatics::ApplyDamage(UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0), 5.0f, GetInstigator()->GetController(), this, UDamageType::StaticClass());
}

void AZombieCharacter::Death()
{
	Destroy();
}
