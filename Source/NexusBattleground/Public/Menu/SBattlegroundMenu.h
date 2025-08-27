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
	Unknown = 0,
	Gameplay = 1,
	MainMenu = 2,
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

	/** Parent Panel to hold current active menu widget */
	TSharedPtr<SBorder> ParentPanel;

	/** Current Active Menu Button */
	TSharedPtr<SButton> CurrentActiveButton;
	
	/** Current Active Menu Widget */
	TSharedPtr<SBattlegroundWidget> CurrentActiveWidget;

	/** Static Top Child Menu (Logo, Player's Name, Score ) */
	TSharedPtr<SBattlegroundWidgetMenuTop> MenuTopWidget;

	/** Default Welcome Screend | Default Home Screen */
	TSharedPtr<SBattlegroundWidget> AbountGameMenu;
	TSharedPtr<SButton> AbountGameButton;
	
	/** User can host a new game */
	TSharedPtr<SBattlegroundWidget> HostGameMenu;
	TSharedPtr<SButton> HostGameButton;
	
	/** User can see and join available games */
	TSharedPtr<SBattlegroundWidget> JoinGameMenu;
	TSharedPtr<SButton> JoinGameButton;
	
	/** User can see and manage inventory items */
	TSharedPtr<SBattlegroundWidget> InventoryMenu;
	TSharedPtr<SButton> InventoryButton;
	
	/** User can change display resolution and quality */
	TSharedPtr<SBattlegroundWidget> DisplaySettingsMenu;
	TSharedPtr<SButton> DisplaySettingsButton;
	
	/** User can change sound volume */
	TSharedPtr<SBattlegroundWidget> SoundSettingsMenu;
	TSharedPtr<SButton> SoundSettingsButton;

	/** User can change key bindings */
	TSharedPtr<SBattlegroundWidget> ControlSettingsMenu;
	TSharedPtr<SButton> ControlSettingsButton;

	/** User can see leaderboards */
	TSharedPtr<SBattlegroundWidget> LeaderboardMenu;
	TSharedPtr<SButton> LeaderboardButton;

	/** User can see saved game lists */
	TSharedPtr<SBattlegroundWidget> RecordedGameMenu;
	TSharedPtr<SButton> RecordedGameButton;

	/** Yes | No | Cancel Dialogbox */
	TSharedPtr<SBattlegroundWidget> MessageboxMenu;
	TSharedPtr<SButton> ExitGameButton;
	
	/** Return to game | just hide widget */
	TSharedPtr<SButton> BackToGameButton;

	
	// -------------
    TSharedPtr<SImage> PickupIconImage;
    TSharedPtr<STextBlock> PickupText;
#pragma endregion Components


private:
#pragma region Configurable & Internal Properties
	EMenuScreens CurrentScreen;
	EChildrenMenus CurrentMenuType;
	bool IsControlsLocked = false;
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
	void BindMenuButtonEvents();
	void BackToGame();
	void ExitApplication();
	#pragma endregion Private Helper Methods


#pragma region Callbacks
	UFUNCTION() void OnSettingsUpdated(ESaveGameTypes type);
	FReply OnMenuButtonClicked(TSharedPtr<SButton> clickedButton, EChildrenMenus menuType);
#pragma endregion Callbacks
};
