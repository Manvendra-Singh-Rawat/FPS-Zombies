#include "MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "ZombieCharacter.h"
#include "MyCharacter.h"
#include "Math/UnrealMathUtility.h"

void AMyGameModeBase::AGameModeBase()
{
	CurrentWaveNumber = 0;
}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
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
