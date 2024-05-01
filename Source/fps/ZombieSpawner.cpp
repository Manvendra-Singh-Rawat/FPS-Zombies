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
	SpawnZombiesAtSpawnPoint();
	UE_LOG(LogTemp, Error, TEXT("Count: %d"), SpawnPointsList.Num());
	
}

void AZombieSpawner::SpawnZombiesAtSpawnPoint()
{
	for (int i = 0; i < 10; i++)
	{
		int RandomSpawnNumber = FMath::RandRange(0, SpawnPointsList.Num());
		AZombieCharacter* Zombie = GetWorld()->SpawnActor<AZombieCharacter>(ZombieCharacterSubClass, SpawnPointsList[0]->GetActorLocation(), SpawnPointsList[0]->GetActorRotation(), ZombieSpawnParameter);
		Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this->GetWorld()))->AddZombiesToZombieActorList(Zombie);
		UE_LOG(LogTemp, Error, TEXT("Zombie count: %d"), Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this->GetWorld()))->GetNumberOfZombiesAlive());
	}
}
