// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBattlegroundWidget.h"

#pragma region Forward Declarations
class SBattlegroundWidgetMenuTop;
//enum class EChildrenMenus : uint8;
#pragma endregion Forward Declarations

enum class EMenuScreens : uint8
{
	Gameplay = 0,
	MainMenu = 1,

};

class NEXUSBATTLEGROUND_API SBattlegroundMenu : public SBattlegroundWidget
{

public:
#pragma region Constructors and Overrides
    SLATE_BEGIN_ARGS(SBattlegroundMenu) {}
        SLATE_ARGUMENT(EAnimationTypes, AnimationType)
		SLATE_ARGUMENT(UWorld*, World)
    SLATE_END_ARGS()

    void Construct(const FArguments& args);
#pragma endregion Constructors and Overrides



private:
#pragma region Components
	UWorld* world;

	/** Static Top Child Menu (Logo, Player's Name, Score ) */
	TSharedPtr<SBattlegroundWidgetMenuTop> MenuTopWidget;

	/** Default Welcome Screend | Default Home Screen */
	TSharedPtr<SCompoundWidget> AbountGameMenu;
	TSharedPtr<SButton> AbountGameButton;
	
	/** User can host a new game */
	TSharedPtr<SCompoundWidget> HostGameMenu;
	TSharedPtr<SButton> HostGameButton;
	
	/** User can see and join available games */
	TSharedPtr<SCompoundWidget> JoinGameMenu;
	TSharedPtr<SButton> JoinGameButton;
	
	/** User can see and manage inventory items */
	TSharedPtr<SCompoundWidget> InventoryMenu;
	TSharedPtr<SButton> InventoryButton;
	
	/** User can change display resolution and quality */
	TSharedPtr<SCompoundWidget> DisplaySettingsMenu;
	TSharedPtr<SButton> DisplaySettingsButton;
	
	/** User can change sound volume */
	TSharedPtr<SCompoundWidget> SoundSettingsMenu;
	TSharedPtr<SButton> SoundSettingsButton;

	/** User can change key bindings */
	TSharedPtr<SCompoundWidget> ControlSettingsMenu;
	TSharedPtr<SButton> ControlSettingsButton;

	/** User can see leaderboards */
	TSharedPtr<SCompoundWidget> LeaderboardMenu;
	TSharedPtr<SButton> LeaderboardButton;

	/** User can see saved game lists */
	TSharedPtr<SCompoundWidget> RecordedGameMenu;
	TSharedPtr<SButton> RecordedGameButton;

	/** Yes | No | Cancel Dialogbox */
	TSharedPtr<SCompoundWidget> MessageboxMenu;
	TSharedPtr<SButton> ExitGameButton;
	
	/** Return to game | just hide widget */
	TSharedPtr<SButton> BackButton;

	
	// -------------
    TSharedPtr<SImage> PickupIconImage;
    TSharedPtr<STextBlock> PickupText;
#pragma endregion Components


private:
#pragma region Configurable & Internal Properties
	EMenuScreens CurrentScreen = EMenuScreens::MainMenu;
#pragma endregion Configurable & Internal Properties


public:
#pragma region Public Methods
	FORCEINLINE UWorld* GetWorld() const { return this->world; }
	void SetCurrentScreen(EMenuScreens newScreen);
#pragma region Public Methods


#pragma region Lifecycle Overrides
	virtual void DestroyWidget() override;
#pragma region Lifecycle Overrides


#pragma region Private Helper Methods
	void RefreshButtons();
	#pragma endregion Private Helper Methods


#pragma region Callbacks
	UFUNCTION() void OnSettingsUpdated(ESaveGameTypes type);
#pragma endregion Callbacks
};
