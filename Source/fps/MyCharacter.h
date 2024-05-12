// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ReloadState_ENUM.h"
#include "MyCharacter.generated.h"

UCLASS()
class FPS_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Shooting")
	USkeletalMeshComponent* BodySkeletalMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Shooting")
	USkeletalMeshComponent* GunSkeletalMesh;
	USceneComponent* MagazineComponent;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* GunMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool isScoped;
	FTimerHandle ADS_TimerHandler;
	bool isSprinting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	UAnimMontage* RifleShootingAnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	UAnimMontage* ShotgunShootingAnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	FVector FireEffectMuzzleLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")

	float RifleDamage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Shooting")
	float RifleRangeUnits;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Shooting")
	float RifleDamageDropOffStartRangeUnits;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Shooting")
	float RifleDamageDropOffPercentage = 50.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	TSubclassOf<AActor> MagazineActor;
	AActor* MagazineActorRef;

	FTimerHandle FiringTimerhandler;
	FHitResult HitRes;
	bool isHit;
	bool isReloading;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	class UNiagaraSystem* MuzzleFlash_VFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health System")
	class UHealthComponent* HealthComponent;

	const E_ReloadState ReloadState {E_ReloadState::ReloadState_DetachMagazine};

private:
	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"), Category = "ADS")
	void AimDownSight(bool ShouldADS);
	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"), Category = "ADS")
	bool ReturnAimDownSightStatus();
	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"), Category = "Sprinting")
	void ToggleSprint();

	bool CanFire();
	UFUNCTION(BlueprintCallable, meta = (AlluwPrivateAccess = "true"), Category = "Shooting")
	void StartFire();
	UFUNCTION(BlueprintCallable, meta = (AlluwPrivateAccess = "true"), Category = "Shooting")
	void StopFire();
	UFUNCTION()
	void Fire();
	double DropOffDamage(FVector PlayerLocation, FVector EnemyPosition);
	UFUNCTION(BlueprintCallable, meta = (AlluwPrivateAccess = "true"), Category = "Shooting")
	void Reload(E_ReloadState ReceivedReloadState);

public:
	void PlayDeadPart();
};