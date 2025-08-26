// Fill out your copyright notice in the Description page of Project Settings.

#pragma region Default System Header Files
#include "SBattlegroundMenu.h"
#pragma endregion Default System Header Files


#pragma region NexusBattleground Header Files
#include "BattlegroundStyles.h"
#pragma endregion NexusBattleground Header Files


#pragma region Constructors and Overrides
void SBattlegroundMenu::Construct(const FArguments& args)
{
    SBattlegroundWidget::SetAnimationType(args._AnimationType);

    ChildSlot
        [
            SNew(SBox).HAlign(HAlign_Fill).VAlign(VAlign_Fill)
                [
                    SNew(SBorder).BorderBackgroundColor(FLinearColor(0.f, 0.f, 0.f, 0.6f)).Padding(30.f)
                        .BorderImage(FBattlegroundStyles::GetBrushStyle(WidgetKeys::BORDER_SIDE_FADE))
                        [
                            SNew(SBox).MaxDesiredWidth(1200.f).MaxDesiredHeight(800.f).HAlign(HAlign_Center).VAlign(VAlign_Center)
                                [
                                    SNew(SVerticalBox)
                                        + SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Center)
                                        [
                                            SNew(STextBlock).Text(FText::FromString("Menu Title"))
                                                .TextStyle(FBattlegroundStyles::GetTextBlockStyle(WidgetKeys::FONT_LARGE_TITLE))
                                        ]
                                        + SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Center).Padding(0, 5, 0, 0)
                                        [
                                            SNew(STextBlock).Text(FText::FromString("Subtitle or Description"))
                                                .TextStyle(FBattlegroundStyles::GetTextBlockStyle(WidgetKeys::FONT_LARGE_TITLE))
                                        ]
                                        + SVerticalBox::Slot().FillHeight(1.f).HAlign(HAlign_Fill).VAlign(VAlign_Fill).Padding(0, 20, 0, 0)
                                        [
                                            SNew(SOverlay)
                                                + SOverlay::Slot()
                                                [
                                                    SNew(SBox).HAlign(HAlign_Fill).VAlign(VAlign_Fill)
                                                        [
                                                            SNew(SImage).Image(FBattlegroundStyles::GetBrushStyle(WidgetKeys::BORDER_SIDE_FADE))
                                                        ]
                                                ]
                                        ]
                                ]
                        ]
                ]
		];
}
#pragma endregion Constructors and Overrides
