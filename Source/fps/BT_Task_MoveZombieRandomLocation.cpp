#include "BT_Task_MoveZombieRandomLocation.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

EBTNodeResult::Type UBT_Task_MoveZombieRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	//A#include "BehaviorTree/BlackboardComponent.h"AIController* OwnerController = Cast<AAIController>(OwnerComponent.GetAIOwner());
	NavigationArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0)->GetWorld());

	if (NavigationArea != nullptr)
	{
		NavigationArea->GetRandomReachablePointInRadius(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), 5000.0f, NavigationLocation);
		OwnerComponent.GetBlackboardComponent()->SetValueAsVector(FName("Random Move To Generated Location"), NavigationLocation);
		DrawDebugSphere(this->GetWorld(), NavigationLocation, 10.0f, 8, FColor::Yellow, false, 10.0f);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}