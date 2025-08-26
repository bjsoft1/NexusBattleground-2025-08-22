#include "BattlegroundSaveGame.h"
#include "Kismet/GameplayStatics.h"

void UBattlegroundSettingsManager::LoadSettings()
{
    if (UGameplayStatics::DoesSaveGameExist(BattlegroundKeys::SAVE_GAME_DEFAULT_SLOT, 0))
        SaveData = Cast<UBattlegroundSaveGame>(UGameplayStatics::LoadGameFromSlot(BattlegroundKeys::SAVE_GAME_DEFAULT_SLOT, 0));
    else 
        SaveData = Cast<UBattlegroundSaveGame>(UGameplayStatics::CreateSaveGameObject(UBattlegroundSaveGame::StaticClass()));
}

void UBattlegroundSettingsManager::SaveSettings() 
{
	UGameplayStatics::SaveGameToSlot(SaveData, BattlegroundKeys::SAVE_GAME_DEFAULT_SLOT, 0);
}
