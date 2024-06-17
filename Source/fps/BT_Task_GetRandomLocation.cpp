#include "BT_Task_GetRandomLocation.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyCharacter.h"
#include "DrawDebugHelpers.h"

EBTNodeResult::Type UBT_Task_GetRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	NavigationArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0)->GetWorld());

	if (NavigationArea != nullptr)
	{
		NavigationArea->GetRandomReachablePointInRadius(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), 5000.0f, NavigationLocation);
		OwnerComponent.GetBlackboardComponent()->SetValueAsVector(FName("RandomMoveToLocation"), NavigationLocation);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}

//void UBT_Task_GetRandomLocation::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
//{
//	UObject* TargetActorObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor");
//
//	//if (UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0) == Cast<AMyCharacter>(TargetActorObject))
//	if (UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0) == Cast<AMyCharacter>(TargetActorObject))
//	{
//		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
//	}
//	else
//	{
//		FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
//	}
//}
