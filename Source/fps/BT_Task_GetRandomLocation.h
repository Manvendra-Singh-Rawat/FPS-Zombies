#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BT_Task_GetRandomLocation.generated.h"

UCLASS()
class FPS_API UBT_Task_GetRandomLocation : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReachableRadius;

private:
	class UNavigationSystemV1* NavigationArea;
	FVector GeneratedRandomLocation;
	FNavLocation NavigationLocation;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
};
