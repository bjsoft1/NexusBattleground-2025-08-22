// Fill out your copyright notice in the Description page of Project Settings.

#pragma region Default System Header Files
#include "BattlegroundMenuController.h"
#include "EngineUtils.h"
#include "Camera/CameraActor.h"
#pragma endregion Default System Header Files


#pragma region NexusBattleground Header Files
#pragma endregion NexusBattleground Header Files


#pragma region Constructors and Overrides
ABattlegroundMenuController::ABattlegroundMenuController(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{

}
#pragma endregion Constructors and Overrides


#pragma region Lifecycle Overrides
void ABattlegroundMenuController::BeginPlay()
{
    Super::BeginPlay();

    int32 cameraCount = 0;
    for (TActorIterator<ACameraActor> it(GetWorld()); it; ++it)
    {
        ACameraActor* camera = *it;

        if (camera && camera->ActorHasTag("MenuCamera"))
        {
            SetViewTarget(camera);
            break;
        }
    }

    // Enable mouse cursor and UI-only input
    APlayerController::bShowMouseCursor = true;
    APlayerController::bEnableClickEvents = true;
    APlayerController::bEnableMouseOverEvents = true;

    FInputModeUIOnly inputMode;
    inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);
    APlayerController::SetInputMode(inputMode);
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