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
	TArray<AActor*> SpawnActorList;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning");
	TSubclassOf<class AZombieCharacter> Zombies;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave");
	int CurrentWaveNumber;

public:
	UFUNCTION()
	void AnActorJustDied(AActor* DiedActor);

	void AddZombiesToZombieActorList(class AZombieCharacter* ZombieCharacter);
	int GetNumberOfZombiesAlive();
};
