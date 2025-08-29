// Fill out your copyright notice in the Description page of Project Settings.

#pragma region Default System Header Files
#include "BattlegroundCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Components/CapsuleComponent.h"
#include "Net/UnrealNetwork.h"
#pragma endregion Default System Header Files


#pragma region NexusBattleground Header Files
#include "BattlegroundPickupManager.h"
#include "BattlegroundGameMode.h"
#include "BattlegroundPickup.h"
#pragma endregion NexusBattleground Header Files


#pragma region Constructors and Overrides
ABattlegroundCharacter::ABattlegroundCharacter(const FObjectInitializer& objectInitializer) : Super(objectInitializer),
WeaponType(EWeaponTypes::WT_None)
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
void ABattlegroundCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABattlegroundCharacter, AnimationStates);
	DOREPLIFETIME(ABattlegroundCharacter, WeaponType);
	DOREPLIFETIME(ABattlegroundCharacter, ServerInventory);
}
#pragma endregion Lifecycle Overrides


#pragma region Public Methods
int16 ABattlegroundCharacter::GetBackpackUsedSpace() 
{
	int16 usedSpace = 0;
	const uint16 capacity = GetBackpackCapacity();

	for (const auto& item : ServerInventory) usedSpace += item.Quantity * BattlegroundUtilities::GetPickupWight(item);

	return usedSpace;
}
bool ABattlegroundCharacter::HasEnoughSpaceForPickup(ABattlegroundPickup* pickupItem)
{
	if (!pickupItem) return false;
	const uint16 itemWeight = BattlegroundUtilities::GetPickupWight(pickupItem->GetRowId()) * pickupItem->GetAmount();

	return GetBackpackFreeSpace() >= itemWeight;
}
#pragma endregion Public Methods


#pragma region Protected Methods
bool ABattlegroundCharacter::CanPickupItem(ABattlegroundPickup* pickupItem)
{
	if (!pickupItem) return false;

	if (!HasEnoughSpaceForPickup(pickupItem)) return false;

	const ABattlegroundGameMode* gameMode = Cast<ABattlegroundGameMode>(GetWorld()->GetAuthGameMode());

	if (!gameMode) return false;
	return gameMode->IsPickupRegistered(pickupItem);
}
#pragma endregion Protected Methods


#pragma region Private Helper Methods
void ABattlegroundCharacter::AttachItemToCharacter(const FInventoryClient& inventoryItem)
{
	USceneComponent* charecterMesh = ACharacter::GetMesh();
	const bool isStaticMesh = BattlegroundUtilities::IsStaticMeshPickup(inventoryItem.RowName);


	if (isStaticMesh && inventoryItem.StaticMesh)
	{
		// If already have attached mesh, Just replace the static mesh
		UStaticMeshComponent* meshComponent = BattlegroundUtilities::FindAttachedMesh<UStaticMeshComponent>
			(this, ACharacter::GetMesh(), inventoryItem.AttachedSocket);

		if (!meshComponent) meshComponent = NewObject<UStaticMeshComponent>(this);

		meshComponent->SetStaticMesh(inventoryItem.StaticMesh);
		meshComponent->AttachToComponent(charecterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, inventoryItem.AttachedSocket);
		meshComponent->RegisterComponent();
	}
	else if (!isStaticMesh && inventoryItem.SkeletalMesh)
	{
		// If already have attached mesh, Just replace the skeletal mesh
		USkeletalMeshComponent* meshComponent = BattlegroundUtilities::FindAttachedMesh<USkeletalMeshComponent>
			(this, ACharacter::GetMesh(), inventoryItem.AttachedSocket);

		if (!meshComponent) meshComponent = NewObject<USkeletalMeshComponent>(this);

		meshComponent->SetSkeletalMesh(inventoryItem.SkeletalMesh);
		meshComponent->AttachToComponent(charecterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, inventoryItem.AttachedSocket);
		meshComponent->RegisterComponent();
	}
}
#pragma endregion Private Helper Methods


#pragma region Pickup Helper Methods
FInventoryServer* ABattlegroundCharacter::AddOrReplaceUniqueItem(ABattlegroundPickup* pickupItem, EPickupTypes pickupType, uint8 subType, bool& updatingInventory, bool& needDisposePickupRequestedItem)
{
	FInventoryServer* uniqueItem = FindServerInventoryByType(pickupType);
	const FName requestedRowName = pickupItem->GetRowId();
	
	if (uniqueItem)
	{
		const FName currentRowName = uniqueItem->RowName;

		if (currentRowName != requestedRowName)
		{
			// Re-initialize pickup item to the new type, Do not dispose the requested pickup item
			// Just reused the requested pickup item, Due to the pickup item already registered in the user 
			// So, If we dispose it, then we need to respawn it again
			pickupItem->InitializePickup(uniqueItem->RowName, 1);

			uniqueItem->RowName = requestedRowName;
		}

		uniqueItem->Subtype = subType;

		needDisposePickupRequestedItem = false;
		updatingInventory = true;

		return uniqueItem;
	}

	FInventoryServer newItem;
	
	newItem.PickupType = pickupType;
	newItem.Subtype = subType;
	newItem.RowName = requestedRowName;
	newItem.Quantity = 1;
	newItem.AttachedSocket = BattlegroundKeys::GetSocketNameByType(pickupType);

	needDisposePickupRequestedItem = true;
	updatingInventory = false;

	// Add new item to inventory, And return the reference, For safe pointer usage
	// If we return the pointer from here, It may cause invalid pointer access due to GC will clean up the current new memory
	return &ServerInventory.Add_GetRef(newItem);
}
#pragma endregion Pickup Helper Methods


#pragma region Input Bindings
#pragma endregion Input Bindings

#pragma region Callbacks
#pragma endregion Callbacks


#pragma region Server/Multicast RPC
void ABattlegroundCharacter::Server_PickupItem_Implementation(ABattlegroundPickup* pickupItem)
{
	if (!pickupItem || !AActor::HasAuthority()) return;

	ABattlegroundGameMode* gameMode = Cast<ABattlegroundGameMode>(AActor::GetWorld()->GetAuthGameMode());
	if (!gameMode) return;

	if (CanPickupItem(pickupItem))
	{
		EPickupTypes pickupType;
		uint8 subType;

		// If Not valid RowName, Just return
		if (!BattlegroundUtilities::ParsePickupRowName(pickupItem->GetRowId(), pickupType, subType)) return;

		NEXUS_WARNING("Datatable ID:%s | Pickup Type: %s", *pickupItem->GetRowId().ToString(), *UEnum::GetValueAsString(pickupType));

		FInventoryServer* serverInventory = nullptr;
		bool updatingInventory = false;
		bool needDisposePickupItem = false;

		switch (pickupType)
		{
		case EPickupTypes::Backpack:
		case EPickupTypes::Helmet:
		case EPickupTypes::Armor:
			serverInventory = this->AddOrReplaceUniqueItem(pickupItem, pickupType, subType, updatingInventory, needDisposePickupItem);
			break;
		default:
			break;
		}

		if (serverInventory)
		{
			// TODO: Play Animation
			if (BattlegroundUtilities::IsListenServer(AActor::GetWorld())) this->OnRep_InventoryUpdated();
		}

		if (needDisposePickupItem)
		{
			gameMode->UnregisterPickup(pickupItem);
			pickupItem->Destroy(true);
		}
	}

}
#pragma endregion Server/Multicast RPC


#pragma region Client/OnRep RPC
void ABattlegroundCharacter::OnRep_AnimationStates()
{
}
void ABattlegroundCharacter::OnRep_InventoryUpdated()
{
	for (auto& serverInventory : this->ServerInventory)
	{
		// Check if we already have this item attached
		if (ClientInventory.ContainsByPredicate([&](const FInventoryClient& existing) { return existing.RowName == serverInventory.RowName; })) continue;

		// Reconstruct full client-side data
		FInventoryClient clientInventory;
		clientInventory.RowName = serverInventory.RowName;
		clientInventory.AttachedSocket = serverInventory.AttachedSocket;
		
		// Get pickup type and subtype
		EPickupTypes pickupType;
		uint8 subType;
		BattlegroundUtilities::ParsePickupRowName(serverInventory.RowName, pickupType, subType);
		clientInventory.PickupType = pickupType;
		clientInventory.Subtype = subType;

		ABattlegroundPickupManager* pickupManager = ABattlegroundPickupManager::GetManager(GetWorld());
		if (!pickupManager) return;

		FPickupData pickupData = pickupManager->GetPickupData(serverInventory.RowName);
		if (!pickupData.IsValid) return;

		if(!pickupData.SkeletalMesh.IsNull()) clientInventory.SkeletalMesh = pickupData.SkeletalMesh.LoadSynchronous();
		if (!pickupData.StaticMesh.IsNull()) clientInventory.StaticMesh = pickupData.StaticMesh.LoadSynchronous();

		// Attach item mesh
		if (BattlegroundUtilities::IsPickupNeedAttachIntoCharecter(serverInventory.RowName)) AttachItemToCharacter(clientInventory);
		// TODO: Attachment for Weapon

		ClientInventory.Add(clientInventory);
	}
}
#pragma endregion Client/OnRep RPC


#pragma region Debug Methods
#pragma endregion Debug Methods

