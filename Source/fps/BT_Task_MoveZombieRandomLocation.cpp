#include "BT_Task_MoveZombieRandomLocation.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

EBTNodeResult::Type UBT_Task_MoveZombieRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
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