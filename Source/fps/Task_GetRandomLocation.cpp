// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_GetRandomLocation.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UTask_GetRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (NavArea != nullptr)
	{
		NavArea->GetRandomReachablePointInRadius(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation(), 10000.0f, GeneratedLocation);

		OwnerComponent.GetBlackboardComponent()->SetValueAsVector(FName("Random Patrol Location"), GeneratedLocation);
		UE_LOG(LogTemp, Warning, TEXT("Generated Location: %s"), *GeneratedLocation.Location.ToString());
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::Failed;
}
