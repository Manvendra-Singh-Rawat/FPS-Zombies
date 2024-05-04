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

private:
	int SpawnZombieCount;
	class AMyGameModeBase* GameMode;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawn", meta = (AllowPrivateAccess = "true"));
	TSubclassOf<class AZombieCharacter> ZombieCharacterSubClass;
	TArray<AActor*> SpawnPointsList;
	FActorSpawnParameters ZombieSpawnParameter;
	FTimerHandle ZombieWaveSpawnTimerHandler;

public:
	void InitiateZombieSpawn(int ZombieCount);

private:
	void SpawnZombies();
};
