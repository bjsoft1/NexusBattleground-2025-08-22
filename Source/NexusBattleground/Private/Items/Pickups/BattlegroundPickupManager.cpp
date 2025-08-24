// Fill out your copyright notice in the Description page of Project Settings.

#pragma region Default System Header Files
#include "BattlegroundPickupManager.h"
#pragma endregion Default System Header Files


#pragma region NexusBattleground Header Files
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
}
#pragma endregion Constructors and Overrides


#pragma region Lifecycle Overrides
void ABattlegroundPickupManager::BeginPlay()
{
    Super::BeginPlay();

    PickupManagers.Add(GetWorld(), this);
}
void ABattlegroundPickupManager::EndPlay(const EEndPlayReason::Type endPlayReason)
{
    Super::EndPlay(endPlayReason);
    PickupManagers.Remove(GetWorld());
}
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

