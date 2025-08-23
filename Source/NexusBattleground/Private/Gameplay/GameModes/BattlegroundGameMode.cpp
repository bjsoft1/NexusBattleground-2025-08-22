#pragma region Default System Header Files
#include "BattlegroundGameMode.h"
#pragma endregion Default System Header Files


#pragma region NexusBattleground Header Files
#include "BattlegroundSpectatorPawn.h"
#include "HumanCharacter.h"
#include "BattlegroundAICharacter.h"
#include "BattlegroundOverlay.h"
#include "BattlegroundPlayerController.h"
#include "BattlegroundReplaySpectatorController.h"
#include "BattlegroundPlayerState.h"
#include "BattlegroundGameState.h"
#pragma endregion NexusBattleground Header Files


#pragma region Constructors and Overrides
ABattlegroundGameMode::ABattlegroundGameMode(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	// Default Pawn Class
	AGameModeBase::DefaultPawnClass = AHumanCharacter::StaticClass();
	AGameModeBase::SpectatorClass = ABattlegroundSpectatorPawn::StaticClass();
	ABattlegroundGameMode::ComputerCharacterClass = ABattlegroundAICharacter::StaticClass();

	// Default HUD Class
	AGameModeBase::HUDClass = ABattlegroundOverlay::StaticClass();

	// Default Controller Class
	AGameModeBase::PlayerControllerClass = ABattlegroundPlayerController::StaticClass();
	AGameModeBase::ReplaySpectatorPlayerControllerClass = ABattlegroundReplaySpectatorController::StaticClass();
	AGameModeBase::PlayerStateClass = ABattlegroundPlayerState::StaticClass();
	AGameModeBase::GameStateClass = ABattlegroundGameState::StaticClass();

	AGameModeBase::bUseSeamlessTravel = FParse::Param(FCommandLine::Get(), TEXT("NoSeamlessTravel")) ? false : true;
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