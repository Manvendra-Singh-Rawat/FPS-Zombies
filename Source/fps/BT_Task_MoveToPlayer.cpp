#include "AIController.h"
#include "ZombieCharacter.h"
#include "MyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BT_Task_MoveToPlayer.h"

EBTNodeResult::Type UBT_Task_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!OwnerComp.GetAIOwner())
	{
		return EBTNodeResult::Failed;
	}

	AAIController* ZombieAIController = OwnerComp.GetAIOwner();
	if (ZombieAIController != nullptr)
	{
		APawn* ZombiePawn = ZombieAIController->GetPawn();
		if (ZombiePawn != nullptr)
		{
			AZombieCharacter* ZombieCharacter = Cast<AZombieCharacter>(ZombiePawn);
			if (ZombieCharacter != nullptr)
			{
				ZombieCharacter->ChangeZombieMoveSpeed(true);
			}
		}
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Succeeded;
	}
}