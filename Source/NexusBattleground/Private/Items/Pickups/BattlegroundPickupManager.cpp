// Fill out your copyright notice in the Description page of Project Settings.

#pragma region Default System Header Files
#include "BattlegroundPickupManager.h"
#pragma endregion Default System Header Files


#pragma region NexusBattleground Header Files
#include "BattlegroundUtilities.h"
#include "BattlegroundItemPickup.h"
#include "BattlegroundWeaponPickup.h"
#pragma endregion NexusBattleground Header Files

// This line defines the static member PickupManagers declared in the header.
// In C++, static class members must be defined in exactly one .cpp file
// so the linker can allocate storage for them. Without this, you'll get
// LNK2001 unresolved external symbol errors.
TMap<UWorld*, ABattlegroundPickupManager*> ABattlegroundPickupManager::PickupManagers;


#pragma region Constructors and Overrides
ABattlegroundPickupManager::ABattlegroundPickupManager(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
    AActor::SetReplicates(true);
    AActor::PrimaryActorTick.bCanEverTick = false;
    AActor::RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    this->PickupClassList.Add(ABattlegroundItemPickup::StaticClass());
    this->PickupClassList.Add(ABattlegroundWeaponPickup::StaticClass());

}
#pragma endregion Constructors and Overrides


#pragma region Lifecycle Overrides
void ABattlegroundPickupManager::BeginPlay()
{
    Super::BeginPlay();

    PickupManagers.Add(GetWorld(), this);

    if(AActor::HasAuthority()) 
        GetWorld()->GetTimerManager().SetTimer(this->SpawnTimerHandle, this, &ABattlegroundPickupManager::SpawnRandomPickup, this->SpawnInterval, true);

}
void ABattlegroundPickupManager::EndPlay(const EEndPlayReason::Type endPlayReason)
{
    Super::EndPlay(endPlayReason);
    PickupManagers.Remove(GetWorld());
}
#pragma endregion Lifecycle Overrides


#pragma region Public Methods
/**
 * Default C++ implementation of GetPickupData.
 *
 * This function provides the default behavior for the BlueprintNativeEvent GetPickupData.
 * If a Blueprint subclass overrides this function, the Blueprint version will be called instead.
 *
 * @param RowName  The name of the row in your datatable or pickup collection to retrieve.
 * @return FPickupData  A copy of the pickup data struct corresponding to RowName.
 *
 * Notes:
 * - The _Implementation suffix is required when implementing a BlueprintNativeEvent in C++.
 * - Returning by value is safe here because it avoids dangling pointers or references.
 * - You can optionally fill this struct with default values or lookup logic (e.g., from a DataTable or TMap).
 */
FPickupData ABattlegroundPickupManager::GetPickupData_Implementation(const FName& rowName)
{
    // Create a new, empty FPickupData struct
    FPickupData data;

    // Return the struct by value (safe for both C++ and Blueprint)
    return data;
}
FPickupData ABattlegroundPickupManager::GetRandomPickupData_Implementation()
{
    // Create a new, empty FPickupData struct
    FPickupData data;

    // Return the struct by value (safe for both C++ and Blueprint)
    return data;
}
FName ABattlegroundPickupManager::GetRandomPickupRow_Implementation()
{
    static FName defaultName = NAME_None;
	return defaultName;
}
#pragma endregion Public Methods


#pragma region Protected Methods
#pragma endregion Protected Methods


#pragma region Private Helper Methods
TSubclassOf<ABattlegroundPickup> ABattlegroundPickupManager::GetPickupClass(EPickupTypes pickupType)
{
    if (pickupType == EPickupTypes::Weapon) return this->PickupClassList[1]; // WeaponPickup
    else return this->PickupClassList[0];
}
uint8 ABattlegroundPickupManager::GetDefaultQuantity(EPickupTypes pickupType, uint8 subType) const
{
    switch (pickupType)
    {
    case EPickupTypes::Ammo:
        return 30;
    case EPickupTypes::Medkit:
    {
        if (EPickupMedkitTypes::Bandage == static_cast<EPickupMedkitTypes>(subType)) return 5;
        return 1;
    }
    default:
        return 1;
    }
}
void ABattlegroundPickupManager::SpawnRandomPickup()
{
    if (!HasAuthority()) return;

    bool bUseLine1 = FMath::RandBool();
    FVector startLocation, endLocation;
    float* progress;

    if (bUseLine1)
    {
        startLocation = this->StartPoint1;
        endLocation = this->EndPoint1;
        progress = &this->Line1Progress;
    }
    else
    {
        startLocation = this->StartPoint2;
        endLocation = this->EndPoint2;
        progress = &this->Line2Progress;
    }

    FVector direction = (endLocation - startLocation).GetSafeNormal();
    float lineLength = FVector::Distance(startLocation, endLocation);

    // Stop spawning if we reached the end
    if (*progress >= lineLength)
    {
        GetWorld()->GetTimerManager().ClearTimer(this->SpawnTimerHandle);
        return;
    }

    // Calculate spawn location along line
    FVector spawnLocation = startLocation + direction * (*progress);

    // Add random margin
    spawnLocation.X += FMath::FRandRange(-this->SpawnMargin, this->SpawnMargin);
    spawnLocation.Y += FMath::FRandRange(-this->SpawnMargin, this->SpawnMargin);
    const FName& pickupRowName = GetRandomPickupRow();
    EPickupTypes pickupType;
    uint8 subType;

    if (BattlegroundUtilities::ParsePickupRowName(pickupRowName, pickupType, subType)) {
        GetRandomPickupData();
        TSubclassOf<ABattlegroundPickup> pickupClass = GetPickupClass(pickupType);

        if (pickupClass)
        {
            FActorSpawnParameters spawnParams;
            spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
            ABattlegroundPickup* newPickup = GetWorld()->SpawnActor<ABattlegroundPickup>(pickupClass, spawnLocation, FRotator::ZeroRotator, spawnParams);
            if (newPickup) newPickup->InitializePickup(pickupRowName, GetDefaultQuantity(pickupType, subType));
        }

        // Move progress forward
        *progress += this->SpawnStep;
    }
}
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

