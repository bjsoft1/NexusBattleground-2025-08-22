// Fill out your copyright notice in the Description page of Project Settings.

#include "SBattlegroundWidgetMenuTop.h"
#include "BattlegroundStyles.h"


void SBattlegroundWidgetMenuTop::Construct(const FArguments& args)
{
    ChildSlot
        [
            SNew(SHorizontalBox)
                // Template Logo
                + SHorizontalBox::Slot().HAlign(HAlign_Left).VAlign(VAlign_Fill)
                [
                    SNew(SImage).DesiredSizeOverride(FVector2D(350, 100))
                        .Image(FBattlegroundStyles::GetBrushStyle(WidgetKeys::BORDER_NEXUS_TEMPLATE_LOGO))
                ]

                // Player Name
                + SHorizontalBox::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Center).Padding(0.0f, 0.0f, 20.0f, 0.0f)
                [
                    SAssignNew(this->PlayerNameTextBlock, STextBlock).Text(FText::FromString(TEXT("Bijay Adhikari")))
                        .Justification(ETextJustify::Right).TextStyle(FBattlegroundStyles::GetTextBlockStyle(WidgetKeys::FONT_Medium_TITLE))
                ]

                // Level Indicator
                + SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Right).VAlign(VAlign_Fill)
                [
                    SNew(SOverlay)
                        + SOverlay::Slot()
                        [
                            SAssignNew(this->PlayerLevelIndicatorImage, SImage).DesiredSizeOverride(FVector2D(100, 100))
                                .Image(FBattlegroundStyles::GetBrushStyle(WidgetKeys::BORDER_PROGRESS_00))
                        ]

                        // Text on top of the image
                        + SOverlay::Slot().HAlign(HAlign_Center).VAlign(VAlign_Center)
                        [
                            SAssignNew(this->PlayerLevelTextBlock, STextBlock).Justification(ETextJustify::Center)
                                .TextStyle(FBattlegroundStyles::GetTextBlockStyle(WidgetKeys::FONT_Medium_TITLE))
                        ]
                ]

        ];
}