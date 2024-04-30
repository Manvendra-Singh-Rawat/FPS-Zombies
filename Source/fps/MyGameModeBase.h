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

public:
	UFUNCTION()
	void AnActorJustDied(AActor* DiedActor);
};
