#include "MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "ZombieCharacter.h"
#include "MyCharacter.h"
#include "ZombieSpawner.h"
#include "Math/UnrealMathUtility.h"

void AMyGameModeBase::AGameModeBase()
{
	CurrentWaveNumber = 0;
	ZombieSpawnCount = 5;
	ZombieIncrementNumber = 2;
}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> TempSpawner;
	UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), AZombieSpawner::StaticClass(), TempSpawner);
	if (!TempSpawner.IsEmpty())
	{
		ZombieSpawnerReference = Cast<AZombieSpawner>(TempSpawner[0]);
		MakeZombieSpawnerSpawnZombies(ZombieSpawnCount);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ZombieSpawnerReference is null"));
	}
}

void AMyGameModeBase::ActorDied(AActor* DiedActor)
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
		ZombieCharacter->PlayDeadPart();

		if (ZombieActorList.IsEmpty())
		{
			ZombieSpawnCount += ZombieIncrementNumber;
			MakeZombieSpawnerSpawnZombies(ZombieSpawnCount);
		}
	}
}

void AMyGameModeBase::CountZombiesForThisWave()
{
	UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), AZombieCharacter::StaticClass(), ZombieActorList);
	CurrentWaveNumber++;
	ChangeWaveNumberForPlayer();
}

void AMyGameModeBase::MakeZombieSpawnerSpawnZombies(int ZombieCount)
{
	ZombieSpawnerReference->InitiateZombieSpawn(ZombieCount);
}
