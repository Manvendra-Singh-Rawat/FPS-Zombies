#include "BT_Task_MoveToLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyCharacter.h"
#include "ZombieCharacter.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBT_Task_MoveToLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (!OwnerComp.GetAIOwner())
    {
        return EBTNodeResult::Failed;
    }
    
    AAIController* ZombieAIController = OwnerComp.GetAIOwner();

    ZombieAIController->MoveToLocation(ZombieAIController->GetBlackboardComponent()->GetValueAsVector(FName("RandomMoveToLocation")), 2.0f);
    return EBTNodeResult::Succeeded;
}

void UBT_Task_MoveToLocation::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    UObject* TargetActorObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor");
    
    if (UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0) == Cast<AMyCharacter>(TargetActorObject))
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
    }
    else
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
    }
}
