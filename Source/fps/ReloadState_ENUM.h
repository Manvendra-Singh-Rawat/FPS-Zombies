// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReloadState_ENUM.generated.h"

UENUM(BlueprintType)
enum E_ReloadState
{
	ReloadState_DetachMagazine	UMETA(DisplayName = "Detach Magazine"),
	ReloadState_DropMagazine	UMETA(DisplayName = "Drop Magazine"),
	ReloadState_SpawnMagazine	UMETA(Displayname = "Spawn Magazine"),
	ReloadState_AttachMagazine	UMETA(DisplayName = "Attach Magazine")
};