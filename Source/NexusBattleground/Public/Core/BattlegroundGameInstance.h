// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BattlegroundGameInstance.generated.h"

#pragma region Forward declaretions
class UBattlegroundSettingsManager;
#pragma endregion Forward declaretions


UCLASS()
class NEXUSBATTLEGROUND_API UBattlegroundGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

#pragma region Friend Declarations
#pragma endregion Friend Declarations


public:
#pragma region Constructors and Overrides
	UBattlegroundGameInstance(const FObjectInitializer& objectInitializer);
	virtual void Init() override;
#pragma endregion Constructors and Overrides


protected:
#pragma region Lifecycle Overrides
#pragma endregion Lifecycle Overrides


private:
#pragma region Components
	UPROPERTY() UBattlegroundSettingsManager* SettingsManager;
#pragma endregion Components


private:
#pragma region Configurable & Internal Properties
#pragma endregion Configurable & Internal Properties


public:
#pragma region Public Inline Methods
	FORCEINLINE UBattlegroundSettingsManager* GetSettingsManager() const { return this->SettingsManager; }
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
