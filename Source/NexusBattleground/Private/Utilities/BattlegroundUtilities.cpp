#include "BattlegroundUtilities.h"
#include "BattlegroundGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"


DEFINE_LOG_CATEGORY(LogNexus);

UBattlegroundSettingsManager* BattlegroundUtilities::GetSettingsManager(const UWorld* world)
{
	if (!world) return nullptr;

	UBattlegroundGameInstance* gameInstance = Cast<UBattlegroundGameInstance>(world->GetGameInstance());
	if (!gameInstance) return nullptr;

	return gameInstance->GetSettingsManager();

}

void BattlegroundUtilities::SetUpdateMouseFocus(UWorld* world, bool isVisibleMenu, bool isNeedMouseEvent)
{
	if (!world) return;

	APlayerController* playerController = UGameplayStatics::GetPlayerController(world, 0);
	if (!playerController) return;

	playerController->bShowMouseCursor = isVisibleMenu;
	playerController->bEnableClickEvents = isNeedMouseEvent;
	playerController->bEnableMouseOverEvents = isNeedMouseEvent;

	if (isVisibleMenu)
	{
		FInputModeUIOnly inputMode;
		inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);
		playerController->SetInputMode(inputMode);
	}
	else
	{
		FInputModeGameOnly inputMode;
		playerController->SetInputMode(inputMode);
	}
}
