// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BattlegroundCharacter.h"
#include "BattlegroundUtilities.h"
#include "HumanCharacter.generated.h"


#pragma region Forward declaretions
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
#pragma endregion Forward declaretions


UCLASS()
class NEXUSBATTLEGROUND_API AHumanCharacter : public ABattlegroundCharacter
{
	GENERATED_BODY()


#pragma region Friend Declarations
#pragma endregion Friend Declarations


public:
#pragma region Constructors and Overrides
	AHumanCharacter(const FObjectInitializer& objectInitializer);
	virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;
#pragma endregion Constructors and Overrides


protected:
#pragma region Lifecycle Overrides
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
#pragma endregion Lifecycle Overrides


private:
#pragma region Components
	USpringArmComponent* CameraBoom;
	UCameraComponent* FollowCamera;

	// -----Inputs-----
	UInputMappingContext* IMC_DefaultMappingContext;
	UInputAction* IA_JumpAction;
	UInputAction* IA_MoveAction;
	UInputAction* IA_LookAction;
	UInputAction* IA_CrouchAction;
	UInputAction* IA_CameraAction;
	UInputAction* IA_PickupAction;
#pragma endregion Components


private:
#pragma region Configurable & Internal Properties
	ECameraModes ActiveCameraMode = ECameraModes::SecondPerson;
	UPROPERTY(ReplicatedUsing = OnRep_ControllerYaw) bool IsUseControllerYaw;
#pragma endregion Configurable & Internal Properties


public:
#pragma region Public Inline Methods
#pragma endregion Public Inline Methods


public:
#pragma region Public Methods
#pragma endregion Public Methods


protected:
#pragma region Protected Methods
#pragma endregion Protected Methods


private:
#pragma region Private Helper Methods
#pragma endregion Private Helper Methods


private:
#pragma region Input Bindings
	void IE_MoveCharacter(const FInputActionValue& actionValue);
	void IE_LookCharacter(const FInputActionValue& actionValue);
	void IE_JumpStartCharacter();
	void IE_JumpEndCharacter();
	void IE_CrouchCharacter();
	void IE_SwitchCameraMode();
	void IE_PickupItem();
#pragma endregion Input Bindings

private:
#pragma region Callbacks
#pragma endregion Callbacks


private:
#pragma region Server/Multicast RPC
	UFUNCTION(Server, Reliable) void ServerSetControllerYaw(bool isEnabled);
#pragma endregion Server/Multicast RPC


private:
#pragma region Client/OnRep RPC
	UFUNCTION() void OnRep_ControllerYaw() { APawn::bUseControllerRotationYaw = this->IsUseControllerYaw; }
#pragma endregion Client/OnRep RPC


private:
#pragma region Debug Methods
#pragma endregion Debug Methods


public:
#pragma region Delegates
#pragma endregion Delegates

};
