// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "BattlegroundOverlay.generated.h"


#pragma region Forward declaretions
enum EDirections : uint8;
#pragma endregion Forward declaretions


UCLASS()
class NEXUSBATTLEGROUND_API ABattlegroundOverlay : public AHUD
{
	GENERATED_BODY()


#pragma region Friend Declarations
#pragma endregion Friend Declarations


public:
#pragma region Constructors and Overrides
	ABattlegroundOverlay(const FObjectInitializer& objectInitializer);
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;
	virtual void DrawHUD() override;
#pragma endregion Constructors and Overrides


protected:
#pragma region Lifecycle Overrides
#pragma endregion Lifecycle Overrides


private:
#pragma region Components
	FCanvasIcon Crosshairs[5];
	UTexture2D* MainHUDTexture;
#pragma endregion Components


private:
#pragma region Configurable & Internal Properties
#pragma endregion Configurable & Internal Properties


public:
#pragma region Public Inline Methods

#pragma endregion Public Inline Methods


public:
#pragma region Public Methods
#pragma endregion Public Methods


protected:
#pragma region Protected Methods
#pragma endregion Protected Methods


private:
#pragma region Private Helper Methods
	void DrawCrosshair(double currentTime, float scaleUI);
#pragma endregion Private Helper Methods


private:
#pragma region Input Bindings
#pragma endregion Input Bindings

private:
#pragma region Callbacks
#pragma endregion Callbacks


private:
#pragma region Server/Multicast RPC
#pragma endregion Server/Multicast RPC


private:
#pragma region Client/OnRep RPC
#pragma endregion Client/OnRep RPC


private:
#pragma region Debug Methods
#pragma endregion Debug Methods


public:
#pragma region Delegates
#pragma endregion Delegates

};
