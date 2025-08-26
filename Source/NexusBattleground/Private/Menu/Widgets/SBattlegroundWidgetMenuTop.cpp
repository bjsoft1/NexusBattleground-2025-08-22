// Fill out your copyright notice in the Description page of Project Settings.

#include "SBattlegroundWidgetMenuTop.h"
#include "BattlegroundStyles.h"
#include "BattlegroundUtilities.h"
#include "BattlegroundSaveGame.h"


void SBattlegroundWidgetMenuTop::Construct(const FArguments& args)
{
    ChildSlot
        [
            SNew(SHorizontalBox)
                // Template Logo
                + SHorizontalBox::Slot().HAlign(HAlign_Left).VAlign(VAlign_Fill)
                [
                    SNew(SImage).DesiredSizeOverride(FVector2D(350, 100))
                        .Image(SlateHelpers::GetBrushStyle(WidgetKeys::BORDER_NEXUS_TEMPLATE_LOGO))
                ]

                // Player Name
                + SHorizontalBox::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Center).Padding(0.0f, 0.0f, 20.0f, 0.0f)
                [
                    SNew(SVerticalBox)
                        + SVerticalBox::Slot()
                        [
                            SAssignNew(this->PlayerScoreIndicatorTextBlock, STextBlock).Text(FText::FromString(TEXT("Score: Loading...")))
                                .Justification(ETextJustify::Right).TextStyle(SlateHelpers::GetTextBlockStyle(WidgetKeys::FONT_NORMAL_BUTTON))
                        ]

                        + SVerticalBox::Slot()
                        [
                            SAssignNew(this->PlayerNameTextBlock, STextBlock).Text(FText::FromString(TEXT("Loading...")))
                                .Justification(ETextJustify::Right).TextStyle(SlateHelpers::GetTextBlockStyle(WidgetKeys::FONT_Medium_TITLE))
                        ]
                ]

                // Level Indicator
                + SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Right).VAlign(VAlign_Fill)
                [
                    SNew(SOverlay)
                        + SOverlay::Slot()
                        [
                            SAssignNew(this->PlayerLevelIndicatorImage, SImage).DesiredSizeOverride(FVector2D(100, 100))
                                .Image(SlateHelpers::GetBrushStyle(WidgetKeys::BORDER_PROGRESS_00))
                        ]

                        // Text on top of the image
                        + SOverlay::Slot().HAlign(HAlign_Center).VAlign(VAlign_Center)
                        [
                            SAssignNew(this->PlayerLevelTextBlock, STextBlock).Text(FText::FromString(TEXT("..."))).Justification(ETextJustify::Center)
                                .TextStyle(SlateHelpers::GetTextBlockStyle(WidgetKeys::FONT_Medium_TITLE))
                        ]
                ]

        ];
}
//

#pragma region Public Methods
void SBattlegroundWidgetMenuTop::RefreshPlayerInfo(UWorld* world)
{
	const UBattlegroundSettingsManager* settingsManager = BattlegroundUtilities::GetSettingsManager(world);
	if (!settingsManager) return;

    const FString& playerName =  settingsManager->GetPlayerName();
    int32 playerLevel = settingsManager->GetPlayerLevel();
    int32 playerScore = settingsManager->GetPlayerScore();
    playerLevel = playerLevel <= 0 ? 1 : playerLevel;

    if (this->PlayerNameTextBlock.IsValid()) this->PlayerNameTextBlock->SetText(FText::FromString(playerName));
    if (this->PlayerLevelTextBlock.IsValid()) this->PlayerLevelTextBlock->SetText(FText::AsNumber(playerLevel));

    const int32 levelScore = GameScoreCalculator::GetScoreForLevel(playerLevel);
    if (this->PlayerScoreIndicatorTextBlock.IsValid())
        this->PlayerScoreIndicatorTextBlock->SetText(FText::FromString(FString::Printf(TEXT("Score: %d/%d"), levelScore, playerScore)));

    // Update level indicator based on player level (0-100)
    if (this->PlayerLevelIndicatorImage.IsValid())
    {
        const uint8 percent = GameScoreCalculator::GetLevelCompletionPercent(levelScore, playerLevel, playerScore);
        FName progressKey = WidgetKeys::GetProgressBorderKey(percent);
        this->PlayerLevelIndicatorImage->SetImage(SlateHelpers::GetBrushStyle(progressKey));
	}
}
#pragma endregion Public Methods
