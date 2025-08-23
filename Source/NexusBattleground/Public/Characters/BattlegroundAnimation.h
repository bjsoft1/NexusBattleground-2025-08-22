// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Animation/AnimInstance.h"
#include "BattlegroundAnimation.generated.h"

class ABattlegroundCharacter;
enum class EAnimationOffsets : uint8;
enum class EWeaponTypes : uint8;

UCLASS()
class NEXUSBATTLEGROUND_API UBattlegroundAnimation : public UAnimInstance
{
	GENERATED_BODY()
	
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float deltaSeconds) override;
	void SetOwnerCharacter();
	ABattlegroundCharacter* HumanCharacter;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = "true")) EAnimationOffsets AnimationOffset;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = "true")) EWeaponTypes WeaponType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = "true")) float CharacterSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = "true")) float MoveDirection;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = "true")) float AimPitch;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = "true")) float AimYaw;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = "true")) bool IsAccelerating;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = "true")) bool IsJumping;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = "true")) bool IsCrouching;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = "true")) bool IsProne;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = "true")) bool IsAiming;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = "true")) bool IsDead;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = "true")) bool IsShouldMove;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = "true")) bool IsPlayingMontage;

};
