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
#include "BattlegroundPickup.h"
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
void ABattlegroundGameMode::RegisterPickup(ABattlegroundPickup* pickupItem)
{
	// checkf will crash in debug if called on a client, which is useful for catching mistakes early.
	// In shipping builds, checkf is compiled out, so it won’t affect performance.
	checkf(HasAuthority(), TEXT("Warning! RegisterPickup called on client!"));
	if (!pickupItem) return;
	SpawnedPickups.Add(pickupItem);
}
void ABattlegroundGameMode::UnregisterPickup(ABattlegroundPickup* pickupItem)
{
	checkf(HasAuthority(), TEXT("Warning! UnregisterPickup called on client!"));
	if (!pickupItem) return;
	SpawnedPickups.RemoveAll([](ABattlegroundPickup* pickup) { return !pickup || pickup->IsPendingKillPending(); });
}
bool ABattlegroundGameMode::IsPickupRegistered(ABattlegroundPickup* pickupItem) const
{
	if (!pickupItem) return false;
	return SpawnedPickups.Contains(pickupItem) && !pickupItem->IsPendingKillPending();
}
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