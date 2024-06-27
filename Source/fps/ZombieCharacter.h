#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ZombieCharacter.generated.h"

UCLASS()
class FPS_API AZombieCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AZombieCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UAIPerceptionComponent* AIPerceptionComponent;
	class UAISenseConfig_Sight* SightConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health System")
	class UHealthComponent* HealthComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	class UWidgetComponent* HealthBarWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Instance")
	UAnimInstance* ZombieAnimationInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
	TArray<UAnimMontage*> ZombieAttackAnimMontage;

private:
	UFUNCTION()
	void isDetectedPlayer(AActor* SourceActor, FAIStimulus Stimulus);

public:
	void PlayDeadPart();
	class AAIController* ReturnZombieAIController();
	
	UFUNCTION(BlueprintCallable)
	void AttackPlayer();
	UFUNCTION(BlueprintCallable)
	void ApplyDamageToPlayer();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ChangeZombieMoveSpeed(bool Decision);
};
