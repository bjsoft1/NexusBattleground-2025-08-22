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
#include "BattlegroundPickupManager.h"
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

	static ConstructorHelpers::FClassFinder<ABattlegroundPickupManager> pickupManagerClass(*AssetsPaths::CLS_PICKUP_MANAGER_PATH);
	if (pickupManagerClass.Succeeded()) this->PickupManagerClass = pickupManagerClass.Class;
}
ABattlegroundGameMode::ABattlegroundGameMode(const FObjectInitializer& objectInitializer, EGameModes currentGameMode) : ABattlegroundGameMode(objectInitializer)
{
	this->CurrentGameMode = currentGameMode;
}
#pragma endregion Constructors and Overrides


#pragma region Lifecycle Overrides
void ABattlegroundGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (AActor::HasAuthority() && this->PickupManagerClass)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AActor::GetWorld()->SpawnActor<ABattlegroundPickupManager>(this->PickupManagerClass, FVector::ZeroVector, FRotator::ZeroRotator, spawnParams);
	}
}
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