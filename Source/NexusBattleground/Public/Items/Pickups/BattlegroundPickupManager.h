// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BattlegroundPickupManager.generated.h"


#pragma region Forward declaretions
struct FPickupData;
#pragma endregion Forward declaretions

UCLASS()
class NEXUSBATTLEGROUND_API ABattlegroundPickupManager : public AActor
{
	GENERATED_BODY()


#pragma region Friend Declarations
#pragma endregion Friend Declarations

public:
#pragma region Constructors and Overrides
	ABattlegroundPickupManager(const FObjectInitializer& objectInitializer);
#pragma endregion Constructors and Overrides


protected:
#pragma region Lifecycle Overrides
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;
#pragma endregion Lifecycle Overrides


private:
#pragma region Components
	/**
	* Maps each UWorld instance to its corresponding ABattlegroundPickupManager.
	* This allows any Pickup item or other actor to easily access the manager for the current world.
	*/
	static TMap<UWorld*, class ABattlegroundPickupManager*> PickupManagers;
#pragma endregion Components


private:
#pragma region Configurable & Internal Properties
#pragma endregion Configurable & Internal Properties


public:
#pragma region Public Inline Methods
	FORCEINLINE static ABattlegroundPickupManager* GetManager(UWorld* World)
	{
		if (!World) return nullptr;

		ABattlegroundPickupManager** found = PickupManagers.Find(World);
		return found ? *found : nullptr;
	}
#pragma endregion Public Inline Methods


public:
#pragma region Public Methods
	// Declares a function that can be called from both C++ and Blueprints
	// BlueprintNativeEvent means:
	//   - This function has a C++ default implementation
	//   - Blueprints can optionally override it to provide custom behavior
	// BlueprintCallable means:
	//   - This function can be called directly from Blueprints
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FPickupData GetPickupData(const FName& rowName);
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

