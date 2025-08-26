// Fill out your copyright notice in the Description page of Project Settings.

#pragma region Default System Header Files
#include "SBattlegroundMenu.h"
#pragma endregion Default System Header Files


#pragma region NexusBattleground Header Files
#include "BattlegroundStyles.h"
#include "SBattlegroundWidgetMenuTop.h"
#include "BattlegroundSaveGame.h"
#pragma endregion NexusBattleground Header Files


#pragma region Constructors and Overrides
void SBattlegroundMenu::Construct(const FArguments& args)
{
    const float DEFAULT_PADDING = 00.0f;
    const float MAX_LEFT_MENU_WIDTH = 400.0f;
    const float MAX_LEFT_MENU_BUTTON_WIDTH = MAX_LEFT_MENU_WIDTH - 50.0f;

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
						+ SHorizontalBox::Slot().FillWidth(0.3).MaxWidth(MAX_LEFT_MENU_WIDTH).Padding(DEFAULT_PADDING)
                        [
                            SNew(SScrollBox).ConsumeMouseWheel(EConsumeMouseWheel::Always).ScrollBarStyle(FBattlegroundStyles::Get(), WidgetKeys::SCROLL_DEFAULT)
                                .ScrollBarVisibility(EVisibility::Collapsed).AnimateWheelScrolling(true).ScrollWhenFocusChanges(EScrollWhenFocusChanges::NoScroll)
                                .NavigationDestination(EDescendantScrollDestination::IntoView)
                                
                                + SScrollBox::Slot()
                                [
                                    SNew(SVerticalBox)

                                        + SVerticalBox::Slot().Padding(FMargin(0.0f, DEFAULT_PADDING / 4.0f))
                                        [
                                            SlateHelpers::CreateMenuButton(this->AbountGameButton, FText::FromString("Abount Game"), EButtonTypes::Menu_Active)
                                        ]
                                        + SVerticalBox::Slot().Padding(FMargin(0.0f, DEFAULT_PADDING / 4.0f))
                                        [
                                            SlateHelpers::CreateMenuButton(this->HostGameButton, FText::FromString("Host Game"), EButtonTypes::Menu_Normal)
                                        ]
                                        + SVerticalBox::Slot().Padding(FMargin(0.0f, DEFAULT_PADDING / 4.0f))
                                        [
                                            SlateHelpers::CreateMenuButton(this->JoinGameButton, FText::FromString("Join Game"), EButtonTypes::Menu_Normal)
                                        ]
                                        + SVerticalBox::Slot().Padding(FMargin(0.0f, DEFAULT_PADDING / 4.0f))
                                        [
                                            SlateHelpers::CreateMenuButton(this->InventoryButton, FText::FromString("Inventory"), EButtonTypes::Menu_Normal)
                                        ]
                                        + SVerticalBox::Slot().Padding(FMargin(0.0f, DEFAULT_PADDING / 4.0f))
                                        [
                                            SlateHelpers::CreateMenuButton(this->DisplaySettingsButton, FText::FromString("Display Settings"), EButtonTypes::Menu_Normal)
                                        ]
                                        + SVerticalBox::Slot().Padding(FMargin(0.0f, DEFAULT_PADDING / 4.0f))
                                        [
                                            SlateHelpers::CreateMenuButton(this->SoundSettingsButton, FText::FromString("Sound Settings"), EButtonTypes::Menu_Normal)
                                        ]
                                        + SVerticalBox::Slot().Padding(FMargin(0.0f, DEFAULT_PADDING / 4.0f))
                                        [
                                            SlateHelpers::CreateMenuButton(this->ControlSettingsButton, FText::FromString("Control Settings"), EButtonTypes::Menu_Normal)
                                        ]
                                        + SVerticalBox::Slot().Padding(FMargin(0.0f, DEFAULT_PADDING / 4.0f))
                                        [
                                            SlateHelpers::CreateMenuButton(this->LeaderboardButton, FText::FromString("Leaderboard"), EButtonTypes::Menu_Normal)
                                        ]
                                        + SVerticalBox::Slot().Padding(FMargin(0.0f, DEFAULT_PADDING / 4.0f))
                                        [
                                            SlateHelpers::CreateMenuButton(this->RecordedGameButton, FText::FromString("Recorded Game"), EButtonTypes::Menu_Normal)
                                        ]
                                        + SVerticalBox::Slot().Padding(FMargin(0.0f, DEFAULT_PADDING / 4.0f))
                                        [
                                            SlateHelpers::CreateMenuButton(this->ExitGameButton, FText::FromString("Quit Game"), EButtonTypes::Menu_Normal)
                                        ]
                                ]
                               
                        ]

                    // Right side body
                    + SHorizontalBox::Slot()
                        .FillWidth(1.0f)
                        .Padding(10)
                        [
                            SNew(SBorder)
                                .Padding(10)
                                [
                                    SNew(STextBlock)
                                        .Text(FText::FromString("Right Body Content"))
                                        .Justification(ETextJustify::Left)
                                ]
                        ]
                ]
        ];

    if (UBattlegroundSettingsManager* settingsManager = BattlegroundUtilities::GetSettingsManager(this->GetWorld()))
    {
        this->MenuTopWidget->RefreshPlayerInfo(this->GetWorld());
        settingsManager->OnSaveGameTypeUpdated.AddRaw(this, &SBattlegroundMenu::OnSettingsUpdated);
    }

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
}
#pragma endregion Lifecycle Overrides


#pragma region Private Helper Methods
void SBattlegroundMenu::RefreshButtons()
{
    if (this->CurrentScreen == EMenuScreens::Gameplay)
    {
        this->MenuTopWidget->SetVisibility(EVisibility::Collapsed);
        this->AbountGameButton->SetVisibility(EVisibility::Collapsed);
        this->HostGameButton->SetVisibility(EVisibility::Collapsed);
        this->JoinGameButton->SetVisibility(EVisibility::Collapsed);
        this->InventoryButton->SetVisibility(EVisibility::Collapsed);
        this->LeaderboardButton->SetVisibility(EVisibility::Collapsed);
        this->RecordedGameButton->SetVisibility(EVisibility::Collapsed);

        this->BackButton->SetVisibility(EVisibility::Visible);
    }
    else
    {
        this->MenuTopWidget->SetVisibility(EVisibility::Visible);
        this->AbountGameButton->SetVisibility(EVisibility::Visible);
        this->HostGameButton->SetVisibility(EVisibility::Visible);
        this->JoinGameButton->SetVisibility(EVisibility::Visible);
        this->InventoryButton->SetVisibility(EVisibility::Visible);
        this->LeaderboardButton->SetVisibility(EVisibility::Visible);
        this->RecordedGameButton->SetVisibility(EVisibility::Visible);

        this->BackButton->SetVisibility(EVisibility::Collapsed);
    }
}
#pragma endregion Private Helper Methods


#pragma region Callbacks
void SBattlegroundMenu::OnSettingsUpdated(ESaveGameTypes type)
{
    if (type == ESaveGameTypes::PlayerData || type == ESaveGameTypes::MAX) this->MenuTopWidget->RefreshPlayerInfo(this->GetWorld());
}
#pragma endregion Callbacks