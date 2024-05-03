#include "MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "ZombieCharacter.h"
#include "MyCharacter.h"
#include "ZombieSpawner.h"
#include "Math/UnrealMathUtility.h"

void AMyGameModeBase::AGameModeBase()
{
	CurrentWaveNumber = 0;
	ZombieCountIncrementPerWave = 5;
}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> TempSpawner;
	UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), AZombieSpawner::StaticClass(), TempSpawner);
	if (!TempSpawner.IsEmpty())
	{
		ZombieSpawnerReference = Cast<AZombieSpawner>(TempSpawner[0]);
		MakeZombieSpawnerSpawnZombies(ZombieCountIncrementPerWave);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ZombieSpawnerReference is null"));
	}
}

void AMyGameModeBase::AnActorJustDied(AActor* DiedActor)
{
	if (Cast<AMyCharacter>(DiedActor) != nullptr)
	{
		AMyCharacter* PlayerCharacter = Cast<AMyCharacter>(DiedActor);
		PlayerCharacter->PlayDeadPart();
	}
	else if (Cast<AZombieCharacter>(DiedActor) != nullptr)
	{
		AZombieCharacter* ZombieCharacter = Cast<AZombieCharacter>(DiedActor);
		ZombieActorList.Remove(DiedActor);
		UE_LOG(LogTemp, Warning, TEXT("Zombies count: %d"), ZombieActorList.Num());
		ZombieCharacter->PlayDeadPart();

		if (ZombieActorList.IsEmpty())
		{
			ZombieCountIncrementPerWave += 2;
			MakeZombieSpawnerSpawnZombies(ZombieCountIncrementPerWave);
		}
	}
}

void AMyGameModeBase::AddZombiesToZombieActorList(AZombieCharacter* ZombieCharacter)
{
	ZombieActorList.Add(ZombieCharacter);
}

int AMyGameModeBase::GetNumberOfZombiesAlive()
{
	return ZombieActorList.Num();
}

void AMyGameModeBase::MakeZombieSpawnerSpawnZombies(int ZombieCount)
{
	ZombieSpawnerReference->SpawnZombiesAtSpawnPoint(ZombieCount);
}
