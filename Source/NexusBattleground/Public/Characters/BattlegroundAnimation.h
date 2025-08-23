// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BattlegroundAnimation.generated.h"

UENUM(BlueprintType)
enum class EAnimationOffsets : uint8
{
	AO_None UMETA(DisplayName = "None"),
	AO_NormalStand UMETA(DisplayName = "Normal Stand"),
	AO_NormalCrouch UMETA(DisplayName = "Normal Crouch"),
	AO_RifleStand UMETA(DisplayName = "Rifle Stand"),
	AO_RifleCrouch UMETA(DisplayName = "Rifle Crouch"),
	AO_RifleStandAim UMETA(DisplayName = "Rifle Stand Aim"),
	AO_RifleCrouchAim UMETA(DisplayName = "Rifle Crouch Aim"),
};

UCLASS()
class NEXUSBATTLEGROUND_API UBattlegroundAnimation : public UAnimInstance
{
	GENERATED_BODY()
	
};
