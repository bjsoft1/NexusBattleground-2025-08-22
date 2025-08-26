// Fill out your copyright notice in the Description page of Project Settings.

#pragma region Default System Header Files
#include "SBattlegroundMenu.h"
#pragma endregion Default System Header Files


#pragma region NexusBattleground Header Files
#include "BattlegroundStyles.h"
#include "SBattlegroundWidgetMenuTop.h"
#pragma endregion NexusBattleground Header Files


#pragma region Constructors and Overrides
void SBattlegroundMenu::Construct(const FArguments& args)
{
    SBattlegroundWidget::SetAnimationType(args._AnimationType);

    ChildSlot
        [
            SNew(SVerticalBox)
			// 01. Top title bar
            + SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Fill).VAlign(VAlign_Top).Padding(20.0f)
                [
                  SAssignNew(this->MenuTopWidget, SBattlegroundWidgetMenuTop)
                ]

			// 02. Bottom body (Left Menu and Right Body)
            + SVerticalBox::Slot().FillHeight(1.0f)
                [
                    SNew(SHorizontalBox)
						// Left side Menu
                        + SHorizontalBox::Slot().AutoWidth()
                        [
                            SNew(SBorder).Padding(10)
                                [
                                    SNew(SVerticalBox)

                                        + SVerticalBox::Slot().AutoHeight().Padding(5)
                                        [
                                            SNew(SBorder).DesiredSizeScale(FVector2D(2.0f))
                                        ]
                                        + SVerticalBox::Slot().AutoHeight().Padding(5)
                                        [
                                            SNew(SButton).Text(FText::FromString("Button 2"))
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
}

#pragma endregion Constructors and Overrides
