#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZombieSpawner.generated.h"

UCLASS()
class FPS_API AZombieSpawner : public AActor
{
	GENERATED_BODY()
	
public:
	AZombieSpawner();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<class AZombieCharacter> ZombieCharacterSubClass;
	TArray<AActor*> SpawnPointsList;
	FActorSpawnParameters ZombieSpawnParameter;

	UFUNCTION()
	void SpawnZombiesAtSpawnPoint(int ZombieCount);

private:
	FTimerHandle ZombieWaveSpawnTimerHandler;

	void SpawnZombies();
	int CountOfZombiesToSpawn;
};
