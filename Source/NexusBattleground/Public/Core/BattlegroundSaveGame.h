// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BattlegroundUtilities.h"
#include "BattlegroundSaveGame.generated.h"

UCLASS()
class NEXUSBATTLEGROUND_API UBattlegroundSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

    // Player info
    UPROPERTY(VisibleAnywhere, Category = "Player Data") FString PlayerName;
    UPROPERTY(VisibleAnywhere, Category = "Player Data") int32 PlayerLevel;
    UPROPERTY(VisibleAnywhere, Category = "Player Data") int32 PlayerScore;

    // Game/Settings options (example)
    UPROPERTY(VisibleAnywhere, Category = "Settings") bool IsMusicOn;
    UPROPERTY(VisibleAnywhere, Category = "Settings") float MasterVolume;
    UPROPERTY(VisibleAnywhere, Category = "Settings") int32 GraphicsQuality;
};

UCLASS()
class NEXUSBATTLEGROUND_API UBattlegroundSettingsManager : public UObject
{
    GENERATED_BODY()

    DECLARE_MULTICAST_DELEGATE_OneParam(FOnSaveGameTypeUpdated, ESaveGameTypes);

private:
    UBattlegroundSaveGame* SaveData;
    void SaveSettings(ESaveGameTypes type);


public:
    FOnSaveGameTypeUpdated OnSaveGameTypeUpdated; 
    void LoadSettings();

    FString GetPlayerName() const { return this->SaveData->PlayerName; }
    void SetPlayerName(const FString& Name) { this->SaveData->PlayerName = Name; this->SaveSettings(ESaveGameTypes::PlayerData); }

	int32 GetPlayerLevel() const { return this->SaveData->PlayerLevel; }
	void SetPlayerLevel(int32 Level) { this->SaveData->PlayerLevel = Level; this->SaveSettings(ESaveGameTypes::PlayerData); }

	int32 GetPlayerScore() const { return this->SaveData->PlayerScore; }
	void SetPlayerScore(int32 Score) { this->SaveData->PlayerScore = Score; this->SaveSettings(ESaveGameTypes::PlayerData); }

    float GetMasterVolume() const { return this->SaveData->MasterVolume; }
    void SetMasterVolume(float Volume) { this->SaveData->MasterVolume = Volume; this->SaveSettings(ESaveGameTypes::AudioSettings); }

    bool GetMusicOn() const { return this->SaveData->IsMusicOn; }
    void SetMusicOn(bool bOn) { this->SaveData->IsMusicOn = bOn; this->SaveSettings(ESaveGameTypes::AudioSettings); }
};
