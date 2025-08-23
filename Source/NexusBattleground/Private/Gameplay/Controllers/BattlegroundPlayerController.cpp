
#pragma region Default System Header Files
#include "BattlegroundPlayerController.h"
#pragma endregion Default System Header Files


#pragma region NexusBattleground Header Files
#include "BattlegroundCheatManager.h"
#include "BattlegroundPlayerCameraManager.h"
#pragma endregion NexusBattleground Header Files


#pragma region Constructors and Overrides
ABattlegroundPlayerController::ABattlegroundPlayerController(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	APlayerController::CheatClass = UBattlegroundCheatManager::StaticClass();
	PlayerCameraManagerClass = ABattlegroundPlayerCameraManager::StaticClass();
}
#pragma endregion Constructors and Overrides


#pragma region Lifecycle Overrides
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