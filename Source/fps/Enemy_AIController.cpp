#include "Enemy_AIController.h"
#include "BehaviorTree/BehaviorTree.h"

void AEnemy_AIController::BeginPlay()
{
	Super::BeginPlay();

	if (EnemyBehaviorTree != nullptr)
	{
		RunBehaviorTree(EnemyBehaviorTree);
	}
}
