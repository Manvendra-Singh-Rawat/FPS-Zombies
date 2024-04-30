#include "MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "ZombieCharacter.h"
#include "MyCharacter.h"

void AMyGameModeBase::AGameModeBase()
{

}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), AZombieCharacter::StaticClass(), ZombieActorList);
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
