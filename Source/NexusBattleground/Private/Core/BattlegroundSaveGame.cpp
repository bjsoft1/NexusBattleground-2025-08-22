#include "BattlegroundSaveGame.h"
#include "Kismet/GameplayStatics.h"

void UBattlegroundSettingsManager::LoadSettings()
{
    if (UGameplayStatics::DoesSaveGameExist(BattlegroundKeys::SAVE_GAME_DEFAULT_SLOT, 0))
        this->SaveData = Cast<UBattlegroundSaveGame>(UGameplayStatics::LoadGameFromSlot(BattlegroundKeys::SAVE_GAME_DEFAULT_SLOT, 0));
    else  this->SaveData = Cast<UBattlegroundSaveGame>(UGameplayStatics::CreateSaveGameObject(UBattlegroundSaveGame::StaticClass()));

    if (!this->SaveData) return;

    if(this->SaveData->PlayerName.IsEmpty()) this->SaveData->PlayerName = FString(FPlatformProcess::UserName());
	if (this->SaveData->PlayerLevel <= 0) this->SaveData->PlayerLevel = 1;
    if (this->SaveData->MasterVolume < 0.0f || this->SaveData->MasterVolume > 1.0f) this->SaveData->MasterVolume = 1.0f;
    if (this->SaveData->GraphicsQuality < 0 || this->SaveData->GraphicsQuality > 3) this->SaveData->GraphicsQuality = 3;

	this->SaveSettings(ESaveGameTypes::MAX);
}

void UBattlegroundSettingsManager::SaveSettings(ESaveGameTypes type)
{
	UGameplayStatics::SaveGameToSlot(SaveData, BattlegroundKeys::SAVE_GAME_DEFAULT_SLOT, 0);
    OnSaveGameTypeUpdated.Broadcast(type);
}
