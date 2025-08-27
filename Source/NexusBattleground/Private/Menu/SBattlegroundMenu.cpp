// Fill out your copyright notice in the Description page of Project Settings.

#pragma region Default System Header Files
#include "SBattlegroundMenu.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#pragma endregion Default System Header Files


#pragma region NexusBattleground Header Files
#include "BattlegroundStyles.h"
#include "SBattlegroundWidgetMenuTop.h"
#include "BattlegroundSaveGame.h"
#pragma endregion NexusBattleground Header Files


#pragma region Constructors and Overrides
void SBattlegroundMenu::Construct(const FArguments& args)
{
    const float DEFAULT_PADDING = 20.0f;
    const FMargin DEFAULT_BUTTON_PADDING = (0.0f, DEFAULT_PADDING / 8.0f);
    SBattlegroundWidget::SetAnimationType(args._AnimationType);
    this->world = args._World;

    ChildSlot
        [
            SNew(SVerticalBox)
                // 01. Top title bar
                + SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Fill).VAlign(VAlign_Top).Padding(DEFAULT_PADDING)
                [
                    SAssignNew(this->MenuTopWidget, SBattlegroundWidgetMenuTop)
                ]

                // 02. Bottom body (Left Menu and Right Body)
                + SVerticalBox::Slot().FillHeight(1.0f)
                [
                    SNew(SHorizontalBox)
                        // Left side Menu buttons
                        + SHorizontalBox::Slot().FillWidth(0.4).MaxWidth(400.0f).Padding(DEFAULT_PADDING)
                        [
                            SNew(SScrollBox).ConsumeMouseWheel(EConsumeMouseWheel::Always).ScrollBarStyle(FBattlegroundStyles::Get(), WidgetKeys::SCROLL_DEFAULT).ScrollBarVisibility(EVisibility::Collapsed).AnimateWheelScrolling(true).ScrollWhenFocusChanges(EScrollWhenFocusChanges::NoScroll).NavigationDestination(EDescendantScrollDestination::IntoView)
                                + SScrollBox::Slot().Padding(DEFAULT_BUTTON_PADDING)
                                [
                                    SlateHelpers::CreateMenuButton(this->AbountGameButton, FText::FromString("Abount Game"), EButtonTypes::Menu_Normal)
                                ]
                                + SScrollBox::Slot().Padding(DEFAULT_BUTTON_PADDING)
                                [
                                    SlateHelpers::CreateMenuButton(this->HostGameButton, FText::FromString("Host Game"), EButtonTypes::Menu_Normal)
                                ]
                                + SScrollBox::Slot().Padding(DEFAULT_BUTTON_PADDING)
                                [
                                    SlateHelpers::CreateMenuButton(this->JoinGameButton, FText::FromString("Join Game"), EButtonTypes::Menu_Normal)
                                ]
                                + SScrollBox::Slot().Padding(DEFAULT_BUTTON_PADDING)
                                [
                                    SlateHelpers::CreateMenuButton(this->InventoryButton, FText::FromString("Inventory"), EButtonTypes::Menu_Normal)
                                ]
                                + SScrollBox::Slot().Padding(DEFAULT_BUTTON_PADDING)
                                [
                                    SlateHelpers::CreateMenuButton(this->DisplaySettingsButton, FText::FromString("Display Settings"), EButtonTypes::Menu_Normal)
                                ]
                                + SScrollBox::Slot().Padding(DEFAULT_BUTTON_PADDING)
                                [
                                    SlateHelpers::CreateMenuButton(this->SoundSettingsButton, FText::FromString("Sound Settings"), EButtonTypes::Menu_Normal)
                                ]
                                + SScrollBox::Slot().Padding(DEFAULT_BUTTON_PADDING)
                                [
                                    SlateHelpers::CreateMenuButton(this->ControlSettingsButton, FText::FromString("Control Settings"), EButtonTypes::Menu_Normal)
                                ]
                                + SScrollBox::Slot().Padding(DEFAULT_BUTTON_PADDING)
                                [
                                    SlateHelpers::CreateMenuButton(this->LeaderboardButton, FText::FromString("Leaderboard"), EButtonTypes::Menu_Normal)
                                ]
                                + SScrollBox::Slot().Padding(DEFAULT_BUTTON_PADDING)
                                [
                                    SlateHelpers::CreateMenuButton(this->RecordedGameButton, FText::FromString("Recorded Game"), EButtonTypes::Menu_Normal)
                                ]
                                + SScrollBox::Slot().Padding(DEFAULT_BUTTON_PADDING)
                                [
                                    SlateHelpers::CreateMenuButton(this->ExitGameButton, FText::FromString("Quit Game"), EButtonTypes::Menu_Normal)
                                ]
                                + SScrollBox::Slot().Padding(DEFAULT_BUTTON_PADDING)
                                [
                                    SlateHelpers::CreateMenuButton(this->BackToGameButton, FText::FromString("Back to Game"), EButtonTypes::Menu_Normal)
                                ]
                        ]

                    // Right side body
                    + SHorizontalBox::Slot().FillWidth(1.0f).Padding(DEFAULT_PADDING)
                        [
                            SAssignNew(this->ParentPanel, SBorder)
                                [
                                    SNew(STextBlock).Text(FText::FromString("Right Body Content"))
                                        .TextStyle(SlateHelpers::GetTextBlockStyle(WidgetKeys::FONT_LARGE_TITLE)).Justification(ETextJustify::Left)
                                ]
                        ]
                ]
        ];

    if (UBattlegroundSettingsManager* settingsManager = BattlegroundUtilities::GetSettingsManager(this->GetWorld()))
    {
        this->MenuTopWidget->RefreshPlayerInfo(this->GetWorld());
        settingsManager->OnSaveGameTypeUpdated.AddRaw(this, &SBattlegroundMenu::OnSettingsUpdated);
    }
    this->BindMenuButtonEvents();
}
#pragma endregion Constructors and Overrides


#pragma region Lifecycle Overrides
void SBattlegroundMenu::SetCurrentScreen(EMenuScreens newScreen)
{
    if (this->CurrentScreen == newScreen) return;
    this->CurrentScreen = newScreen;

    this->RefreshButtons();
}
void SBattlegroundMenu::DestroyWidget()
{
    if (UBattlegroundSettingsManager* settingsManager = BattlegroundUtilities::GetSettingsManager(this->GetWorld()))
        settingsManager->OnSaveGameTypeUpdated.RemoveAll(this);

    if (GEngine->GetWorld() && GEngine->GetWorld()->GetGameViewport())
        GEngine->GetWorld()->GetGameViewport()->RemoveViewportWidgetContent(SharedThis(this));

    this->ParentPanel->ClearContent();
    this->ParentPanel = nullptr;
    this->CurrentActiveWidget = nullptr;

    this->AbountGameMenu = nullptr;
    this->HostGameMenu = nullptr;
    this->JoinGameMenu = nullptr;
    this->InventoryMenu = nullptr;
    this->DisplaySettingsMenu = nullptr;
    this->SoundSettingsMenu = nullptr;
    this->ControlSettingsMenu = nullptr;
    this->LeaderboardMenu = nullptr;
    this->RecordedGameMenu = nullptr;
    this->MessageboxMenu = nullptr;

    this->CurrentActiveButton = nullptr;
    this->MenuTopWidget = nullptr;
    this->AbountGameButton = nullptr;
    this->HostGameButton = nullptr;
    this->JoinGameButton = nullptr;
    this->InventoryButton = nullptr;
    this->DisplaySettingsButton = nullptr;
    this->SoundSettingsButton = nullptr;
    this->ControlSettingsButton = nullptr;
    this->LeaderboardButton = nullptr;
    this->RecordedGameButton = nullptr;
    this->ExitGameButton = nullptr;
    this->BackToGameButton = nullptr;
}
#pragma endregion Lifecycle Overrides


#pragma region Private Helper Methods
void SBattlegroundMenu::RefreshButtons()
{
    if (this->CurrentScreen == EMenuScreens::Gameplay)
    {
        //this->MenuTopWidget->SetVisibility(EVisibility::Collapsed);
        //this->AbountGameButton->SetVisibility(EVisibility::Collapsed);
        //this->HostGameButton->SetVisibility(EVisibility::Collapsed);
        //this->JoinGameButton->SetVisibility(EVisibility::Collapsed);
        //this->InventoryButton->SetVisibility(EVisibility::Collapsed);
        //this->LeaderboardButton->SetVisibility(EVisibility::Collapsed);
        //this->RecordedGameButton->SetVisibility(EVisibility::Collapsed);
        //
        //this->BackToGameButton->SetVisibility(EVisibility::Visible);

		// Default to display settings when in-game
        this->OnMenuButtonClicked(this->DisplaySettingsButton, EChildrenMenus::DisplaySettings);
    }
    else
    {
        //this->AbountGameButton->SetVisibility(EVisibility::Visible);
        //this->MenuTopWidget->SetVisibility(EVisibility::Visible);
        //this->HostGameButton->SetVisibility(EVisibility::Visible);
        //this->JoinGameButton->SetVisibility(EVisibility::Visible);
        //this->InventoryButton->SetVisibility(EVisibility::Visible);
        //this->LeaderboardButton->SetVisibility(EVisibility::Visible);
        //this->RecordedGameButton->SetVisibility(EVisibility::Visible);
        //
        //this->BackToGameButton->SetVisibility(EVisibility::Collapsed);

		// Default to AbountGame when in main menu
        this->OnMenuButtonClicked(this->AbountGameButton, EChildrenMenus::AbountGame);
    }
}
void SBattlegroundMenu::BindMenuButtonEvents()
{
    this->AbountGameButton->SetOnClicked(FOnClicked::CreateSP(this, &SBattlegroundMenu::OnMenuButtonClicked, this->AbountGameButton, EChildrenMenus::AbountGame));
    this->HostGameButton->SetOnClicked(FOnClicked::CreateSP(this, &SBattlegroundMenu::OnMenuButtonClicked, this->HostGameButton, EChildrenMenus::HostGame));
    this->JoinGameButton->SetOnClicked(FOnClicked::CreateSP(this, &SBattlegroundMenu::OnMenuButtonClicked, this->JoinGameButton, EChildrenMenus::JoinGame));
    this->InventoryButton->SetOnClicked(FOnClicked::CreateSP(this, &SBattlegroundMenu::OnMenuButtonClicked, this->InventoryButton, EChildrenMenus::Inventory));
    this->DisplaySettingsButton->SetOnClicked(FOnClicked::CreateSP(this, &SBattlegroundMenu::OnMenuButtonClicked, this->DisplaySettingsButton, EChildrenMenus::DisplaySettings));
    this->SoundSettingsButton->SetOnClicked(FOnClicked::CreateSP(this, &SBattlegroundMenu::OnMenuButtonClicked, this->SoundSettingsButton, EChildrenMenus::SoundSettings));
    this->ControlSettingsButton->SetOnClicked(FOnClicked::CreateSP(this, &SBattlegroundMenu::OnMenuButtonClicked, this->ControlSettingsButton, EChildrenMenus::ControlSettings));
    this->LeaderboardButton->SetOnClicked(FOnClicked::CreateSP(this, &SBattlegroundMenu::OnMenuButtonClicked, this->LeaderboardButton, EChildrenMenus::Leaderboard));
    this->RecordedGameButton->SetOnClicked(FOnClicked::CreateSP(this, &SBattlegroundMenu::OnMenuButtonClicked, this->RecordedGameButton, EChildrenMenus::RecordedGame));
    this->ExitGameButton->SetOnClicked(FOnClicked::CreateSP(this, &SBattlegroundMenu::OnMenuButtonClicked, this->ExitGameButton, EChildrenMenus::ExitGame));
    this->BackToGameButton->SetOnClicked(FOnClicked::CreateSP(this, &SBattlegroundMenu::OnMenuButtonClicked, this->BackToGameButton, EChildrenMenus::BackToGame));
           
    this->SetCurrentScreen(EMenuScreens::MainMenu);
}
void SBattlegroundMenu::BackToGame()
{
    this->OverrideVisibility(false);
}
void SBattlegroundMenu::ExitApplication()
{
    if (GEngine->GameViewport)
    {
        this->IsControlsLocked = true;
        GEngine->GameViewport->ConsoleCommand("quit");
    }
}
#pragma endregion Private Helper Methods


#pragma region Callbacks
void SBattlegroundMenu::OnSettingsUpdated(ESaveGameTypes type)
{
    if (this->IsControlsLocked) return;

    if (type == ESaveGameTypes::PlayerData || type == ESaveGameTypes::MAX) this->MenuTopWidget->RefreshPlayerInfo(this->GetWorld());
}
FReply SBattlegroundMenu::OnMenuButtonClicked(TSharedPtr<SButton> clickedButton, EChildrenMenus menuType)
{
    if (this->IsControlsLocked || menuType == this->CurrentMenuType) return FReply::Handled();

    if (menuType == EChildrenMenus::ExitGame)
    {
        this->ExitApplication();
        return FReply::Handled();
    }
    else if (menuType == EChildrenMenus::BackToGame)
    {
        this->BackToGame();
        return FReply::Handled();
	}

    this->CurrentMenuType = menuType;
    if (this->CurrentActiveWidget.IsValid()) this->CurrentActiveWidget->OverrideVisibility(false);

    const auto normalButtonStyle = &SlateHelpers::GetButtonStyle(EButtonTypes::Menu_Normal);
    const auto activeButtonStyle = &SlateHelpers::GetButtonStyle(EButtonTypes::Menu_Active);

    if (this->CurrentActiveButton) this->CurrentActiveButton->SetButtonStyle(normalButtonStyle);
    if (clickedButton) clickedButton->SetButtonStyle(activeButtonStyle);

    this->CurrentActiveButton = clickedButton;

    switch (menuType)
    {
    case EChildrenMenus::MAX:
        break;
    case EChildrenMenus::AbountGame:
        break;
    case EChildrenMenus::HostGame:
        break;
    case EChildrenMenus::JoinGame:
        break;
    case EChildrenMenus::Inventory:
        break;
    case EChildrenMenus::DisplaySettings:
        break;
    case EChildrenMenus::SoundSettings:
        break;
    case EChildrenMenus::ControlSettings:
        break;
    case EChildrenMenus::Leaderboard:
        break;
    case EChildrenMenus::RecordedGame:
        break;
    default:
        break;
    }

    return FReply::Handled();
}
#pragma endregion Callbacks