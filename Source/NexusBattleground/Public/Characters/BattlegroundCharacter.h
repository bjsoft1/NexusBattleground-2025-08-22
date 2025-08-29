// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BattlegroundUtilities.h"
#include "BattlegroundCharacter.generated.h"


#pragma region Forward declaretions
#pragma endregion Forward declaretions


UCLASS()
class NEXUSBATTLEGROUND_API ABattlegroundCharacter : public ACharacter
{
	GENERATED_BODY()


#pragma region Friend Declarations
#pragma endregion Friend Declarations


public:
#pragma region Constructors and Overrides
	ABattlegroundCharacter(const FObjectInitializer& objectInitializer);
#pragma endregion Constructors and Overrides


protected:
#pragma region Lifecycle Overrides
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
#pragma endregion Lifecycle Overrides


protected:
#pragma region Components
#pragma endregion Components


private:
#pragma region Configurable & Internal Properties
	UPROPERTY(ReplicatedUsing = OnRep_AnimationStates) EAnimationStates AnimationStates = EAnimationStates::None;
	UPROPERTY(Replicated) EWeaponTypes WeaponType;

	// Inventory Helpers
	UPROPERTY(ReplicatedUsing = OnRep_InventoryUpdated) TArray<FInventoryServer> ServerInventory;
	UPROPERTY() TArray<FInventoryClient> ClientInventory;

#pragma endregion Configurable & Internal Properties


public:
#pragma region Public Inline Methods
	FORCEINLINE bool IsFalling() const { return ACharacter::GetCharacterMovement()->IsFalling(); }
	FORCEINLINE bool IsCrouched() const { return ACharacter::GetCharacterMovement()->IsCrouching(); }
	FORCEINLINE bool IsAccelerating() const { return !ACharacter::GetCharacterMovement()->GetCurrentAcceleration().IsNearlyZero(); }
	FORCEINLINE FVector GetMovementVelocity() const { return ACharacter::GetCharacterMovement()->Velocity; }
	FORCEINLINE FVector GetCurrentAcceleration() const { return ACharacter::GetCharacterMovement()->GetCurrentAcceleration(); }
	FORCEINLINE EWeaponTypes GetWeaponType() const { return this->WeaponType; }

	FORCEINLINE bool HasAnimationFlag(EAnimationStates flag) const { return (static_cast<uint8>(this->AnimationStates) & static_cast<uint8>(flag)) != 0; }
	FORCEINLINE bool IsAiming() const { return (this->AnimationStates & EAnimationStates::IsAiming) != EAnimationStates::None; }
	FORCEINLINE bool IsReloading() const { return (this->AnimationStates & EAnimationStates::IsReloading) != EAnimationStates::None; }
	FORCEINLINE bool IsWeaponEquipped() const { return (this->AnimationStates & EAnimationStates::IsWeaponEquipped) != EAnimationStates::None; }
	FORCEINLINE bool IsDead() const { return false; }
	FORCEINLINE bool IsPlayingMontage() const { return (this->AnimationStates & EAnimationStates::IsPlayingMontage) != EAnimationStates::None; }
	FORCEINLINE bool IsFreeFalling() const { return (this->AnimationStates & EAnimationStates::IsFreeFalling) != EAnimationStates::None; }
	FORCEINLINE bool IsParachuteOpen() const { return (this->AnimationStates & EAnimationStates::IsParachuteOpen) != EAnimationStates::None; }

	FORCEINLINE int16 GetBackpackCapacity() { return BattlegroundUtilities::GetBackpackCapacity(FindServerInventoryByType(EPickupTypes::Backpack)); }
	FORCEINLINE int16 GetBackpackFreeSpace() { return GetBackpackCapacity() - GetBackpackUsedSpace(); }
#pragma endregion Public Inline Methods


public:
#pragma region Public Methods
	int16 GetBackpackUsedSpace();
	bool HasEnoughSpaceForPickup(ABattlegroundPickup* pickupItem);
#pragma endregion Public Methods


protected:
#pragma region Protected Methods
	bool CanPickupItem(ABattlegroundPickup* pickupItem);
#pragma endregion Protected Methods


private:
#pragma region Private Helper Methods
	void AttachItemToCharacter(const FInventoryClient& Item);

	FORCEINLINE FInventoryServer* FindServerInventoryByType(EPickupTypes pickupType) { return this->ServerInventory.FindByPredicate([&](FInventoryServer& item) { return item.PickupType == pickupType; }); }
	FORCEINLINE FInventoryClient* FindInventoryByType_Subtype(EPickupTypes pickupType, uint8 subType) { return this->ClientInventory.FindByPredicate([&](FInventoryClient& item) { return item.PickupType == pickupType && item.Subtype == subType; }); }
#pragma endregion Private Helper Methods


private:
#pragma region Pickup Helper Methods
	/**
	* This method will add or replace unique item in the inventory.
	* If not exists, it will be added.
	* If exists, it will be replaced SubType and Update Pickup Item Properties in Level, To make sure it will re-able to pickup again.
	*/
	FInventoryServer* AddOrReplaceUniqueItem(ABattlegroundPickup* pickupItem, EPickupTypes pickupType, uint8 subType, bool& updatingInventory, bool& needDisposePickupRequestedItem);
#pragma endregion Pickup Helper Methods


private:
#pragma region Input Bindings
#pragma endregion Input Bindings

private:
#pragma region Callbacks
#pragma endregion Callbacks


protected:
#pragma region Server/Multicast RPC
	UFUNCTION(Server, Reliable) void Server_PickupItem(ABattlegroundPickup* pickupItem);
#pragma endregion Server/Multicast RPC


private:
#pragma region Client/OnRep RPC
	UFUNCTION() void OnRep_AnimationStates();
	UFUNCTION() void OnRep_InventoryUpdated();
#pragma endregion Client/OnRep RPC


private:
#pragma region Debug Methods
#pragma endregion Debug Methods


public:
#pragma region Delegates
#pragma endregion Delegates

};
