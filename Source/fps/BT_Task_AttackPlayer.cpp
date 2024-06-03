#include "BT_Task_AttackPlayer.h"
#include "ZombieCharacter.h"

EBTNodeResult::Type UBT_Task_AttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	APawn* TempPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (TempPawn != nullptr)
	{
		AZombieCharacter* ZombieCharacterRef = Cast<AZombieCharacter>(TempPawn);
		if (ZombieCharacterRef != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Working"));
			ZombieCharacterRef->AttackPlayer();
			return EBTNodeResult::Succeeded;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Failed 2"));
			return EBTNodeResult::Failed;
		}
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}
