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
    else
    {
        /*AAIController* ZombieAIController = OwnerComp.GetAIOwner();
        if (ZombieAIController != nullptr)
        {
            APawn* ZombiePawn = ZombieAIController->GetPawn();
            if (ZombiePawn != nullptr)
            {
                AZombieCharacter* ZombieCharacter = Cast<AZombieCharacter>(ZombiePawn);
                if (ZombieCharacter != nullptr)
                {
                    ZombieCharacter->AhhLoL();
                }
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("AI Controller is null"));
        }*/
    }
    
    AAIController* ZombieAIController = OwnerComp.GetAIOwner();

    ZombieAIController->MoveToLocation(OwnerComp.GetBlackboardComponent()->GetValueAsVector(FName("RandomMoveToLocation")), 5.0f);
    return EBTNodeResult::Succeeded;
}

void UBT_Task_MoveToLocation::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    UObject* TargetActorObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor");
    
    if (UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0) == Cast<AMyCharacter>(TargetActorObject))
    {
        //AAIController* ZombieAIController = OwnerComp.GetAIOwner();
        //if (ZombieAIController != nullptr)
        //{
        //    APawn* ZombiePawn = ZombieAIController->GetPawn();
        //    if (ZombiePawn != nullptr)
        //    {
        //        AZombieCharacter* ZombieCharacter = Cast<AZombieCharacter>(ZombiePawn);
        //        if (ZombieCharacter != nullptr)
        //        {
        //            ZombieCharacter->AhhLoL();
        //        }
        //    }
        //}
        //else
        //{
        //    UE_LOG(LogTemp, Error, TEXT("Zombie AI Controlelr is null"));
        //}
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
    }
    else
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
    }
}
