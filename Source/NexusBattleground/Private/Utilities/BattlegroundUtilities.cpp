#include "BattlegroundUtilities.h"
#include "BattlegroundGameInstance.h"

DEFINE_LOG_CATEGORY(LogNexus);

const FString AssetsPaths::DEFAULT_WIDGET_STYLE_PATH = ASSET_PATH(TEXT("Styles"));

const FString AssetsPaths::SKM_FEMALE_PATH = ASSET_PATH(TEXT("Characters/Mannequins/Meshes/SKM_Quinn_Simple"));
const FString AssetsPaths::SKM_MALE_PATH = ASSET_PATH(TEXT("Characters/Mannequins/Meshes/SKM_Manny_Simple"));

const FString AssetsPaths::ANIM_FEMALE_PATH = ASSET_PATH(TEXT("Blueprints/Animations/BP_BattlegroundAnimation"));

const FString AssetsPaths::CLS_PICKUP_MANAGER_PATH = ASSET_PATH(TEXT("Blueprints/Pickups/BP_BattlegroundPickupManager"));

const FString AssetsPaths::TX2D_MAIN_HUD_PATH = ASSET_PATH(TEXT("Assets/HUD/TX_HUDMain"));

UBattlegroundSettingsManager* BattlegroundUtilities::GetSettingsManager(const UWorld* world)
{
	if (!world) return nullptr;

	UBattlegroundGameInstance* gameInstance = Cast<UBattlegroundGameInstance>(world->GetGameInstance());
	if (!gameInstance) return nullptr;

	return gameInstance->GetSettingsManager();

}
