#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

UCLASS()
class FPS_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	void AGameModeBase();

	virtual void BeginPlay() override;

private:
	TArray<AActor*> ZombieActorList;
	class AZombieSpawner* ZombieSpawnerReference;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WaveSystem", meta = (AllowPrivateAccess = "true"));
	TSubclassOf<class AZombieCharacter> Zombies;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WaveSystem", meta = (AllowPrivateAccess = "true"));
	int CurrentWaveNumber;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WaveSystem", meta = (AllowPrivateAccess = "true"));
	int ZombieSpawnCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WaveSystem", meta = (AllowPrivateAccess = "true"));
	int ZombieIncrementNumber;

public:
	void ActorDied(AActor* DiedActor);
	void CountZombiesForThisWave();

	UFUNCTION(BlueprintImplementableEvent, meta = (AllowPrivateAccess = "true"))
	void ChangeWaveNumberForPlayer();

private:
	void MakeZombieSpawnerSpawnZombies(int ZombieCount);
};
