// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class FPS_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


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
	UAnimMontage* RifleShootingAnimMontage_HIP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	UAnimMontage* ShotgunShootingAnimMontage_HIP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	UAnimMontage* RifleShootingAnimMontage_IRONSIGHT;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	UAnimMontage* ShotgunShootingAnimMontage_IRONSIGHT;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	FVector FireEffectMuzzleLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	class UAnimMontage* RifleShootingAnimMontage;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Shooting")
	FTimerHandle FiringTimerhandler;
	FHitResult HitRes;
	bool isHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	class UNiagaraSystem* FireEffectMuzzle;

private:
	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"), Category = "ADS")
	void AimDownSight(bool ShouldADS);
	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"), Category = "ADS")
	bool ReturnAimDownSightStatus();
	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"), Category = "Sprinting")
	void ToggleSprint();

	UFUNCTION(BlueprintCallable, meta = (AlluwPrivateAccess = "true"), Category = "Shooting")
	bool CanFire();
	UFUNCTION(BlueprintCallable, meta = (AlluwPrivateAccess = "true"), Category = "Shooting")
	void StartFire();
	UFUNCTION(BlueprintCallable, meta = (AlluwPrivateAccess = "true"), Category = "Shooting")
	void StopFire();
	UFUNCTION(BlueprintCallable, meta = (AlluwPrivateAccess = "true"), Category = "Shooting")
	void Fire();
	UFUNCTION(BlueprintCallable, meta = (AlluwPrivateAccess = "true"), Category = "Shooting")
	void Reload();
};