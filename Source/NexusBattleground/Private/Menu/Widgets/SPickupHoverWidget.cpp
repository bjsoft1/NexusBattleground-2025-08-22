// Fill out your copyright notice in the Description page of Project Settings.

#pragma region Default System Header Files
#include "SPickupHoverWidget.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Text/STextBlock.h"
#include "Engine/Texture2D.h"
#pragma endregion Default System Header Files


#pragma region NexusBattleground Header Files
#include "BattlegroundStyles.h"
#pragma endregion NexusBattleground Header Files


#pragma region Constructors and Overrides
void SPickupHoverWidget::Construct(const FArguments& args)
{
    SBattlegroundWidget::SetAnimationType(args._AnimationType);

    ChildSlot
        [
            SNew(SBox).HAlign(HAlign_Left).VAlign(VAlign_Fill)
                [
                    SNew(SBorder).BorderBackgroundColor(FLinearColor(0.f, 0.f, 0.f, 0.6f)).Padding(30.f)
                        .BorderImage(SlateHelpers::GetBrushStyle(WidgetKeys::BORDER_SIDE_FADE))
                        [
                            SNew(SBox).MaxDesiredWidth(600.f).MaxDesiredHeight(500.f).HAlign(HAlign_Center).VAlign(VAlign_Center)
                                [
                                    SNew(SVerticalBox)
                                        + SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Center)
                                        [
                                            SAssignNew(this->PickupIconImage, SImage).DesiredSizeOverride(FVector2D(200, 200))
                                        ]
                                        + 
                                        SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Center).Padding(0, 5, 0, 0)
                                        [
                                            SAssignNew(this->PickupText, STextBlock).Text(FText::FromString("Item Name"))
                                                .TextStyle(SlateHelpers::GetTextBlockStyle(WidgetKeys::FONT_LARGE_TITLE))
                                        ]
                                        + SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Center)
                                        [
                                            SNew(STextBlock).Text(FText::FromString("Press E to pick up"))
                                                .TextStyle(SlateHelpers::GetTextBlockStyle(WidgetKeys::FONT_Medium_TITLE))
                                        ]
                                ]
                        ]
                ]
        ];
}
#pragma endregion Constructors and Overrides


#pragma region Public Methods
void SPickupHoverWidget::SetItemData(UTexture2D* itemIcon, const FText& itemName)
{
    if (this->PickupIconImage.IsValid() && itemIcon) this->PickupIconImage->SetImage(WidgetHelpers::FSlateBrushFromTexture(itemIcon));
    if (this->PickupText.IsValid()) this->PickupText->SetText(itemName);
}
#pragma endregion Public Methods
