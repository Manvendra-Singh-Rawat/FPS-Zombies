#include "ZombieSpawner.h"
#include "ZombieCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "MyGameModeBase.h"

AZombieSpawner::AZombieSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
	ZombieSpawnParameter.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
}

void AZombieSpawner::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClassWithTag(this->GetWorld(), AActor::StaticClass(), TEXT("SpawnZombieActorPoints"), SpawnPointsList);
	GameMode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this->GetWorld()));
}

void AZombieSpawner::InitiateZombieSpawn(int ZombieCount)
{
	SpawnZombieCount = ZombieCount;
	GetWorld()->GetTimerManager().SetTimer(ZombieWaveSpawnTimerHandler, this, &AZombieSpawner::SpawnZombies, 5.0f, false, 5.0f);
}

void AZombieSpawner::SpawnZombies()
{
	for (int i = 0; i < SpawnZombieCount; i++)
	{
		int RandomSpawnNumber = FMath::RandRange(0, SpawnPointsList.Num() - 1);
		AZombieCharacter* Zombie = GetWorld()->SpawnActor<AZombieCharacter>(ZombieCharacterSubClass, SpawnPointsList[RandomSpawnNumber]->GetActorLocation(), SpawnPointsList[RandomSpawnNumber]->GetActorRotation(), ZombieSpawnParameter);
	}
	GameMode->CountZombiesForThisWave();
	GetWorld()->GetTimerManager().ClearTimer(ZombieWaveSpawnTimerHandler);
}
