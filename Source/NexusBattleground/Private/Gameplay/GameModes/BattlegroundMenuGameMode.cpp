// Fill out your copyright notice in the Description page of Project Settings.

#pragma region Default System Header Files
#include "BattlegroundMenuGameMode.h"
#pragma endregion Default System Header Files


#pragma region NexusBattleground Header Files
#include "BattlegroundMenuController.h"
#include "SBattlegroundMenu.h"
#include "BattlegroundUtilities.h"
#include "BattlegroundSaveGame.h"
#pragma endregion NexusBattleground Header Files


#pragma region Constructors and Overrides
ABattlegroundMenuGameMode::ABattlegroundMenuGameMode(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
    DefaultPawnClass = nullptr;
    HUDClass = nullptr;
	PlayerControllerClass = ABattlegroundMenuController::StaticClass();
}
#pragma endregion Constructors and Overrides


#pragma region Lifecycle Overrides
void ABattlegroundMenuGameMode::BeginPlay()
{
    Super::BeginPlay();

	// Only create the menu widget on clients and listen servers
    if (AActor::GetWorld() && !AActor::GetWorld()->IsNetMode(NM_DedicatedServer))
    {
        SAssignNew(this->MainMenuWidget, SBattlegroundMenu).AnimationType(EAnimationTypes::MoveLeft_Right).World(AActor::GetWorld());
        this->MainMenuWidget->SetVisibility(EVisibility::Collapsed);

        FTimerHandle timerHandle;
        GetWorldTimerManager().SetTimer(timerHandle, this, &ABattlegroundMenuGameMode::ShowMainMenu, DEFAULT_MAIN_MENU_DELAY, false);
    }
}
#pragma endregion Lifecycle Overrides


#pragma region Public Methods
#pragma endregion Public Methods


#pragma region Protected Methods
#pragma endregion Protected Methods


#pragma region Private Helper Methods
void ABattlegroundMenuGameMode::ShowMainMenu()
{
    GEngine->GameViewport->AddViewportWidgetContent(MainMenuWidget.ToSharedRef());
	this->MainMenuWidget->OverrideVisibility(true);
}
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