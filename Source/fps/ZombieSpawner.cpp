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
}

void AZombieSpawner::SpawnZombiesAtSpawnPoint(int ZombieCount)
{
	CountOfZombiesToSpawn = ZombieCount;
	GetWorld()->GetTimerManager().SetTimer(ZombieWaveSpawnTimerHandler, this, &AZombieSpawner::SpawnZombies, 5.0f, false, 5.0f);
}

void AZombieSpawner::SpawnZombies()
{
	for (int i = 0; i < CountOfZombiesToSpawn; i++)
	{
		int RandomSpawnNumber = FMath::RandRange(0, SpawnPointsList.Num() - 1);
		AZombieCharacter* Zombie = GetWorld()->SpawnActor<AZombieCharacter>(ZombieCharacterSubClass, SpawnPointsList[RandomSpawnNumber]->GetActorLocation(), SpawnPointsList[RandomSpawnNumber]->GetActorRotation(), ZombieSpawnParameter);
		Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this->GetWorld()))->AddZombiesToZombieActorList(Zombie);
		UE_LOG(LogTemp, Warning, TEXT("ZOMBIE: Zombie count: %d"), Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this->GetWorld()))->GetNumberOfZombiesAlive());
	}
	GetWorld()->GetTimerManager().ClearTimer(ZombieWaveSpawnTimerHandler);
}
