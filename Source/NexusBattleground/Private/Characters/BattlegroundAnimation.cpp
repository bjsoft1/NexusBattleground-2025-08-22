// Fill out your copyright notice in the Description page of Project Settings.


#include "BattlegroundAnimation.h"
#include "BattlegroundCharacter.h"
#include "Kismet/KismetMathLibrary.h"

void UBattlegroundAnimation::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	this->SetOwnerCharacter();
}
void UBattlegroundAnimation::NativeUpdateAnimation(float deltaSeconds)
{
	Super::NativeUpdateAnimation(deltaSeconds);

	if (!this->HumanCharacter)
	{
		this->SetOwnerCharacter();
		return;
	}


	const FVector velocity = this->HumanCharacter->GetVelocity();
	const FRotator rotation = this->HumanCharacter->GetActorRotation();
	const FRotator controlRotation = this->HumanCharacter->GetControlRotation();

	FRotator aimRotation = UKismetMathLibrary::NormalizedDeltaRotator(controlRotation, rotation);
	this->AimPitch = aimRotation.Pitch;

	// Smooth with frame-rate independent interpolation
	static float continuousYaw = this->AimYaw;
	float yawSpeed = 3.0f; // Higher = faster
	continuousYaw = FMath::FInterpTo(continuousYaw, aimRotation.Yaw, deltaSeconds, yawSpeed);
	this->AimYaw = FRotator::NormalizeAxis(continuousYaw);

	//this->MovementVelocity = this->HumanCharacter->GetMovementVelocity();
	this->CharacterSpeed = velocity.Size2D();
	this->MoveDirection = UAnimInstance::CalculateDirection(velocity, rotation);
	this->IsAccelerating = this->HumanCharacter->IsAccelerating();
	this->IsJumping = this->HumanCharacter->IsFalling();
	this->IsCrouching = this->HumanCharacter->IsCrouched();
	this->IsAiming = this->HumanCharacter->IsAiming();
	this->WeaponType = this->HumanCharacter->GetWeaponType();
	this->IsDead = this->HumanCharacter->IsDead();
	this->IsShouldMove = UKismetMathLibrary::NotEqual_VectorVector(FVector::ZeroVector, this->HumanCharacter->GetCurrentAcceleration()) && this->CharacterSpeed > 3.0f;
	this->IsPlayingMontage = this->HumanCharacter->IsPlayingMontage();
}
void UBattlegroundAnimation::SetOwnerCharacter()
{
	this->HumanCharacter = Cast<ABattlegroundCharacter>(TryGetPawnOwner());
}
