// Fill out your copyright notice in the Description page of Project Settings.

#pragma region Default System Header Files
#include "BattlegroundOverlay.h"
#pragma endregion Default System Header Files


#pragma region NexusBattleground Header Files
#include "BattlegroundUtilities.h"
#include "HumanCharacter.h"
#pragma endregion NexusBattleground Header Files


#pragma region Constructors and Overrides
ABattlegroundOverlay::ABattlegroundOverlay(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> hudMainTexture(*AssetsPaths::TX2D_MAIN_HUD_PATH);
	this->MainHUDTexture = hudMainTexture.Object;

	// Extract crosshair icons from the HUD texture
	this->Crosshairs[EDirections::Left] = UCanvas::MakeIcon(this->MainHUDTexture, 43, 402, 25, 9);
	this->Crosshairs[EDirections::Right] = UCanvas::MakeIcon(this->MainHUDTexture, 88, 402, 25, 9);
	this->Crosshairs[EDirections::Top] = UCanvas::MakeIcon(this->MainHUDTexture, 74, 371, 9, 25);
	this->Crosshairs[EDirections::Bottom] = UCanvas::MakeIcon(this->MainHUDTexture, 74, 415, 9, 25);
	this->Crosshairs[EDirections::Center] = UCanvas::MakeIcon(this->MainHUDTexture, 75, 403, 7, 7);
}
void ABattlegroundOverlay::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);
}
void ABattlegroundOverlay::DrawHUD()
{
	Super::DrawHUD();

	if (Canvas == nullptr || !AHUD::GetOwningPawn()) return;

	AHumanCharacter* character = CastChecked<AHumanCharacter>(AHUD::GetOwningPawn());
	if (!character) return;

	float scaleUI = Canvas->ClipY / 1080.0f;
	const double currentTime = GetWorld()->GetTimeSeconds();

	this->DrawCrosshair(currentTime, scaleUI);
}

#pragma endregion Constructors and Overrides


#pragma region Lifecycle Overrides
#pragma endregion Lifecycle Overrides


#pragma region Public Methods
#pragma endregion Public Methods


#pragma region Protected Methods
#pragma endregion Protected Methods


#pragma region Private Helper Methods
void ABattlegroundOverlay::DrawCrosshair(double currentTime, float scaleUI)
{
	float centerX = AHUD::Canvas->ClipX / 2;
	float centerY = AHUD::Canvas->ClipY / 2;
	float crossSpread = 20; // TODO: Make this configurable

	AHUD::Canvas->SetDrawColor(210, 210, 210, 100);

	// Draw the crosshair
	AHUD::Canvas->DrawIcon(this->Crosshairs[EDirections::Center],
		centerX - (this->Crosshairs[EDirections::Center]).UL * scaleUI / 2.0f,
		centerY - (this->Crosshairs[EDirections::Center]).VL * scaleUI / 2.0f, scaleUI);

	AHUD::Canvas->DrawIcon(this->Crosshairs[EDirections::Left],
		centerX - 1 - (this->Crosshairs[EDirections::Left]).UL * scaleUI - crossSpread * scaleUI,
		centerY - (this->Crosshairs[EDirections::Left]).VL * scaleUI / 2.0f, scaleUI);
	AHUD::Canvas->DrawIcon(this->Crosshairs[EDirections::Right],
		centerX + crossSpread * scaleUI,
		centerY - (this->Crosshairs[EDirections::Right]).VL * scaleUI / 2.0f, scaleUI);

	AHUD::Canvas->DrawIcon(this->Crosshairs[EDirections::Top],
		centerX - (this->Crosshairs[EDirections::Top]).UL * scaleUI / 2.0f,
		centerY - 1 - (this->Crosshairs[EDirections::Top]).VL * scaleUI - crossSpread * scaleUI, scaleUI);
	AHUD::Canvas->DrawIcon(this->Crosshairs[EDirections::Bottom],
		centerX - (this->Crosshairs[EDirections::Bottom]).UL * scaleUI / 2.0f,
		centerY + crossSpread * scaleUI, scaleUI);
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

