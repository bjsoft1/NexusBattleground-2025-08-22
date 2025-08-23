// Fill out your copyright notice in the Description page of Project Settings.

#pragma region Default System Header Files
#include "HumanCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "Components/InputComponent.h"
#include "UObject/UObjectGlobals.h"
#include "Net/UnrealNetwork.h"
#pragma endregion Default System Header Files


#pragma region NexusBattleground Header Files
#include "BattlegroundCharacterMovementComponent.h"
#pragma endregion NexusBattleground Header Files


#pragma region Constructors and Overrides
AHumanCharacter::AHumanCharacter(const FObjectInitializer& objectInitializer) 
	: Super(objectInitializer.SetDefaultSubobjectClass<UBattlegroundCharacterMovementComponent>(ACharacter::CharacterMovementComponentName)),
	ActiveCameraMode(ECameraModes::CM_SecondPerson)
{
	// Find Inputs
	ConstructorHelpers::FObjectFinder<UInputMappingContext> inputMappingContext(ASSET_PATH(TEXT("Inputs/IMC_NexusInputContext")));
	ConstructorHelpers::FObjectFinder<UInputAction> jumpAction(ASSET_PATH(TEXT("Inputs/Actions/IA_Jump")));
	ConstructorHelpers::FObjectFinder<UInputAction> moveAction(ASSET_PATH(TEXT("Inputs/Actions/IA_Move")));
	ConstructorHelpers::FObjectFinder<UInputAction> lookAction(ASSET_PATH(TEXT("Inputs/Actions/IA_Look")));
	ConstructorHelpers::FObjectFinder<UInputAction> crouchAction(ASSET_PATH(TEXT("Inputs/Actions/IA_Crouch")));
	ConstructorHelpers::FObjectFinder<UInputAction> cameraAction(ASSET_PATH(TEXT("Inputs/Actions/IA_Camera")));
	ConstructorHelpers::FObjectFinder<UInputAction> pickupAction(ASSET_PATH(TEXT("Inputs/Actions/IA_Pickup")));

	this->IMC_DefaultMappingContext = inputMappingContext.Object;
	this->IA_JumpAction = jumpAction.Object;
	this->IA_MoveAction = moveAction.Object;
	this->IA_LookAction = lookAction.Object;
	this->IA_CrouchAction = crouchAction.Object;
	this->IA_CameraAction = cameraAction.Object;
	this->IA_PickupAction = pickupAction.Object;
}
void AHumanCharacter::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(playerInputComponent))
	{
		//Jumping
		enhancedInputComponent->BindAction(this->IA_JumpAction, ETriggerEvent::Started, this, &AHumanCharacter::IE_JumpStartCharacter);
		enhancedInputComponent->BindAction(this->IA_JumpAction, ETriggerEvent::Completed, this, &AHumanCharacter::IE_JumpEndCharacter);

		// Basic Movement
		enhancedInputComponent->BindAction(this->IA_MoveAction, ETriggerEvent::Triggered, this, &AHumanCharacter::IE_MoveCharacter);
		enhancedInputComponent->BindAction(this->IA_LookAction, ETriggerEvent::Triggered, this, &AHumanCharacter::IE_LookCharacter);

		// Crouch/Uncrouch/Prone/Unprone
		enhancedInputComponent->BindAction(this->IA_CrouchAction, ETriggerEvent::Started, this, &AHumanCharacter::IE_CrouchCharacter);

		// Utilities
		enhancedInputComponent->BindAction(this->IA_CameraAction, ETriggerEvent::Started, this, &AHumanCharacter::IE_SwitchCameraMode);
		enhancedInputComponent->BindAction(this->IA_PickupAction, ETriggerEvent::Started, this, &AHumanCharacter::IE_PickupItem);
	}
}
#pragma endregion Constructors and Overrides


#pragma region Lifecycle Overrides
void AHumanCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* playerController = Cast<APlayerController>(GetController()))
	{
		if (playerController->IsLocalController())
		{
			if (ACharacter::GetMesh())
			{
				// Create Spring Arm
				this->CameraBoom = NewObject<USpringArmComponent>(this, USpringArmComponent::StaticClass(), TEXT("DynamicCameraBoom"));
				this->CameraBoom->bUsePawnControlRotation = true;
				this->CameraBoom->bEnableCameraLag = true;

				// Register with the actor so it exists in the world
				this->CameraBoom->RegisterComponent();
				this->CameraBoom->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, HEAD_CAMERA_SOCKET);

				// Create Camera
				this->FollowCamera = NewObject<UCameraComponent>(this, UCameraComponent::StaticClass(), TEXT("DynamicFollowCamera"));
				this->FollowCamera->bUsePawnControlRotation = false;

				// Register & attach
				this->FollowCamera->RegisterComponent();
				this->FollowCamera->AttachToComponent(this->CameraBoom, FAttachmentTransformRules::SnapToTargetIncludingScale, USpringArmComponent::SocketName);

				this->IE_SwitchCameraMode();
			}

			if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
				subsystem->AddMappingContext(this->IMC_DefaultMappingContext, 0);
		}
	}
}
void AHumanCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AHumanCharacter, IsUseControllerYaw);
}
#pragma endregion Lifecycle Overrides


#pragma region Public Methods
#pragma endregion Public Methods


#pragma region Protected Methods
#pragma endregion Protected Methods


#pragma region Private Helper Methods
#pragma endregion Private Helper Methods


#pragma region Input Bindings
void AHumanCharacter::IE_MoveCharacter(const FInputActionValue& actionValue)
{
	const FVector2D movement = actionValue.Get<FVector2D>();
	if (!APawn::Controller && movement.IsNearlyZero()) return;

	const FRotator yawRotation(0.f, APawn::Controller->GetControlRotation().Yaw, 0.f);
	APawn::AddMovementInput(FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X), movement.Y);
	APawn::AddMovementInput(FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y), movement.X);
}
void AHumanCharacter::IE_LookCharacter(const FInputActionValue& actionValue)
{
	const FVector2D lookInput = actionValue.Get<FVector2D>();

	if (Controller && !lookInput.IsNearlyZero())
	{
		// Add yaw input (turn left/right)
		AddControllerYawInput(lookInput.X);

		// Add pitch input (look up/down)
		AddControllerPitchInput(lookInput.Y);
	}
}
void AHumanCharacter::IE_JumpStartCharacter()
{
	if (this->IsCrouched())
	{
		IE_CrouchCharacter();
		return;
	}

	// TODO: Detact wall for climb on the wall.

	ACharacter::Jump();
}
void AHumanCharacter::IE_JumpEndCharacter()
{
	ACharacter::StopJumping();
}
void AHumanCharacter::IE_CrouchCharacter()
{
	if (this->IsCrouched()) ACharacter::UnCrouch();
	else ACharacter::Crouch();
}
void AHumanCharacter::IE_SwitchCameraMode()
{
	if (!this->CameraBoom) return;

	int32 next = ((int32)this->ActiveCameraMode + 1) % 3;
	this->ActiveCameraMode = static_cast<ECameraModes>(next);

	switch (this->ActiveCameraMode)
	{
	case ECameraModes::CM_FirstPerson:
		this->IsUseControllerYaw = APawn::bUseControllerRotationYaw = true;
		this->CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 0.0f);
		this->CameraBoom->TargetArmLength = 0.0f;
		this->CameraBoom->CameraLagSpeed = 30.0f;
		this->CameraBoom->bEnableCameraRotationLag = false;
		break;
	case ECameraModes::CM_SecondPerson:
		this->CameraBoom->TargetArmLength = 100.0f;
		this->CameraBoom->CameraLagSpeed = 25.0f;
		this->CameraBoom->CameraRotationLagSpeed = 25.0f;
		this->CameraBoom->bEnableCameraRotationLag = true;
		this->CameraBoom->SocketOffset = FVector(0.0f, 20.0f, 20.0f);
		this->IsUseControllerYaw = APawn::bUseControllerRotationYaw = true;
		break;
	case ECameraModes::CM_ThirdPerson:
		this->CameraBoom->TargetArmLength = 200.0f;
		this->CameraBoom->CameraLagSpeed = 20.0f;
		this->CameraBoom->CameraRotationLagSpeed = 20.0f;
		this->CameraBoom->bEnableCameraRotationLag = true;
		this->CameraBoom->SocketOffset = FVector(0.0f, 20.0f, 20.0f);
		this->IsUseControllerYaw = APawn::bUseControllerRotationYaw = false;
		break;
	}

	if (!AActor::HasAuthority()) ServerSetControllerYaw(this->IsUseControllerYaw);
	else OnRep_ControllerYaw();
}
void AHumanCharacter::IE_PickupItem()
{
	int32 next = ((int32)this->WeaponType + 1) % 3;
	this->WeaponType = static_cast<EWeaponTypes>(next);
}
#pragma endregion Input Bindings

#pragma region Callbacks
#pragma endregion Callbacks


#pragma region Server/Multicast RPC
void AHumanCharacter::ServerSetControllerYaw_Implementation(bool isEnabled)
{
	this->IsUseControllerYaw = isEnabled;
	this->OnRep_ControllerYaw();
}
#pragma endregion Server/Multicast RPC


#pragma region Client/OnRep RPC
#pragma endregion Client/OnRep RPC


#pragma region Debug Methods
#pragma endregion Debug Methods

