#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BT_Task_AttackPlayer.generated.h"

UCLASS()
class FPS_API UBT_Task_AttackPlayer : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
	
private:
	//virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class AZombieCharacter* ZombieCharacterRef;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class AMyCharacter* PlayerCharacterRef;
};
