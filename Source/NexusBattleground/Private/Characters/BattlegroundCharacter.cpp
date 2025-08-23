// Fill out your copyright notice in the Description page of Project Settings.

#pragma region Default System Header Files
#include "BattlegroundCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Components/CapsuleComponent.h"

#pragma endregion Default System Header Files


#pragma region NexusBattleground Header Files
#include "BattlegroundUtilities.h"
#pragma endregion NexusBattleground Header Files


#pragma region Constructors and Overrides
ABattlegroundCharacter::ABattlegroundCharacter(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{

	// Setup Character Mesh
	ConstructorHelpers::FObjectFinder<USkeletalMesh> characterMesh(*AssetsPaths::SKM_FEMALE_PATH);
	ConstructorHelpers::FClassFinder<UAnimInstance> characterAnimation(*AssetsPaths::ANIM_FEMALE_PATH);

	ACharacter::GetMesh()->SetSkeletalMesh(characterMesh.Object);
	ACharacter::GetMesh()->SetWorldLocation(FVector(0.0f, 0.0f, -90.0f));
	ACharacter::GetMesh()->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));

	// Setup Character Animation
	ACharacter::GetMesh()->SetAnimInstanceClass(characterAnimation.Class);

	// Don't rotate when the controller rotates. Let that just affect the camera.

	APawn::bUseControllerRotationPitch = false;
	// Handled from IA_SwitchCameraMode
	//APawn::bUseControllerRotationYaw = true;
	APawn::bUseControllerRotationRoll = false;

	// Configure character movement
	ACharacter::GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	ACharacter::GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate
	ACharacter::GetCapsuleComponent()->SetHiddenInGame(true, true);

	// Adjust movement parameters for smoother character movement
	ACharacter::GetCharacterMovement()->BrakingFrictionFactor = 0.5f; // Increase braking friction for smoother stops
	ACharacter::GetCharacterMovement()->MaxAcceleration = 1000.0f; // Increase acceleration for smoother start
	ACharacter::GetCharacterMovement()->GroundFriction = 100.0f; // Increase ground friction for smoother movement
	ACharacter::GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f; // Adjust deceleration for smoother stops
	ACharacter::GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Optionally, you can adjust other parameters like MaxWalkSpeed, AirControl, and JumpZVelocity for your desired movement behavior
	ACharacter::GetCharacterMovement()->MaxWalkSpeed = DEFAULT_MAX_WALK_SPEED; // Adjust maximum walk speed
	ACharacter::GetCharacterMovement()->MaxWalkSpeedCrouched = DEFAULT_MAX_CROUCHED_WALK_SPEED; // Movement speed while crouched
	ACharacter::GetCharacterMovement()->AirControl = 0.35f; // Adjust air control for smoother mid-air movement
	ACharacter::GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	ACharacter::GetCharacterMovement()->JumpZVelocity = 450.f; // Adjust jump velocity
	ACharacter::GetCharacterMovement()->NavAgentProps.bCanCrouch = true; // Enabled Crouch Property
	ACharacter::GetCapsuleComponent()->SetCapsuleHalfHeight(DEFAULT_CAPSULE_HALF_HEIGHT);
	ACharacter::GetCharacterMovement()->SetCrouchedHalfHeight(CROUCH_CAPSULE_HALF_HEIGHT);

}
#pragma endregion Constructors and Overrides


#pragma region Lifecycle Overrides
#pragma endregion Lifecycle Overrides


#pragma region Public Methods
#pragma endregion Public Methods


#pragma region Protected Methods
#pragma endregion Protected Methods


#pragma region Private Helper Methods
#pragma endregion Private Helper Methods


#pragma region Input Bindings
#pragma endregion Input Bindings

#pragma region Callbacks
#pragma endregion Callbacks


#pragma region Server/Multicast RPC
#pragma endregion Server/Multicast RPC


#pragma region Client/OnRep RPC
#pragma endregion Client/OnRep RPC


#pragma region Debug Methods
#pragma endregion Debug Methods

