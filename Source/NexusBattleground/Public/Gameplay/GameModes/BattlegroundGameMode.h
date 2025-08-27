// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BattlegroundGameMode.generated.h"


#pragma region Forward declaretions
enum class EGameModes : uint8;
class ABattlegroundPickup;
#pragma endregion Forward declaretions


UCLASS()
class NEXUSBATTLEGROUND_API ABattlegroundGameMode : public AGameMode
{
	GENERATED_BODY()


#pragma region Friend Declarations
#pragma endregion Friend Declarations


public:
#pragma region Constructors and Overrides
	ABattlegroundGameMode(const FObjectInitializer & objectInitializer);
	ABattlegroundGameMode(const FObjectInitializer & objectInitializer, EGameModes currentGameMode);
#pragma endregion Constructors and Overrides


protected:
#pragma region Lifecycle Overrides
	virtual void BeginPlay() override;
#pragma endregion Lifecycle Overrides


protected:
#pragma region Components
	UPROPERTY() TSubclassOf<class ABattlegroundPickupManager> PickupManagerClass;
	UPROPERTY() TSubclassOf<APawn> ComputerCharacterClass;

	UPROPERTY() TArray<ABattlegroundPickup*> SpawnedPickups;
#pragma endregion Components


private:
#pragma region Configurable & Internal Properties
	EGameModes CurrentGameMode;
	const float MinRespawnDelay = 3.0f;
	bool IsAllowComputerCharacter;
#pragma endregion Configurable & Internal Properties


public:
#pragma region Public Inline Methods

#pragma endregion Public Inline Methods


public:
#pragma region Public Methods
	void RegisterPickup(ABattlegroundPickup* pickupItem);
	void UnregisterPickup(ABattlegroundPickup* pickupItem);
	bool IsPickupRegistered(ABattlegroundPickup* pickupItem) const;
#pragma endregion Public Methods


protected:
#pragma region Protected Methods
#pragma endregion Protected Methods


private:
#pragma region Private Helper Methods
#pragma endregion Private Helper Methods


private:
#pragma region Input Bindings
#pragma endregion Input Bindings

private:
#pragma region Callbacks
#pragma endregion Callbacks


private:
#pragma region Server/Multicast RPC
#pragma endregion Server/Multicast RPC


private:
#pragma region Client/OnRep RPC
#pragma endregion Client/OnRep RPC


private:
#pragma region Debug Methods
#pragma endregion Debug Methods


public:
#pragma region Delegates
#pragma endregion Delegates

};
