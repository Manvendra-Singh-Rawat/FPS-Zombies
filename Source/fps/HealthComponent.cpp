#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameModeBase.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	MaxHealth = 100.0f;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;

	AActor* Owner = GetOwner();
	if (Owner != nullptr)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::ActorOnTakeAnyDamage);
	}
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::ActorOnTakeAnyDamage(AActor* DamagedActor, float DamageReceived, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (DamageReceived <= 0.0f)
	{
		return;
	}

	CurrentHealth = CurrentHealth - DamageReceived;
	if (CurrentHealth <= 0.0f)
	{
		CurrentHealth = 0.0f;
		MyCustomGameMode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this->GetWorld()));
		MyCustomGameMode->ActorDied(DamagedActor);
	}
}
