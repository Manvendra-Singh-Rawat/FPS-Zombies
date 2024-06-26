#include "AIController.h"
#include "MyCharacter.h"
#include "ZombieCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BT_Task_AttackPlayer.h"

EBTNodeResult::Type UBT_Task_AttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	if (!OwnerComponent.GetAIOwner())
	{
		return EBTNodeResult::Failed;
	}

	PlayerCharacterRef = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(this->GetWorld(), 0));
	if (PlayerCharacterRef == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AAIController* ZombieAIController = OwnerComponent.GetAIOwner();
	if (ZombieAIController != nullptr)
	{
		APawn* ZombiePawn = ZombieAIController->GetPawn();
		if (ZombiePawn != nullptr)
		{
			ZombieCharacterRef = Cast<AZombieCharacter>(ZombiePawn);
			if (ZombieCharacterRef == nullptr)
			{
				return EBTNodeResult::Failed;
			}
		}
		else
		{
			return EBTNodeResult::Failed;
		}
	}
	else
	{
		return EBTNodeResult::Failed;
	}
	
	return EBTNodeResult::Succeeded;
}
