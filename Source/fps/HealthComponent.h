#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"));
	float MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"));
	float CurrentHealth;
	class AMyGameModeBase* MyCustomGameMode;

public:
	UFUNCTION()
	void ActorOnTakeAnyDamage(AActor* DamagedActor, float DamageReceived, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
};
