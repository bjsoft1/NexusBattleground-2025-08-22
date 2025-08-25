// Fill out your copyright notice in the Description page of Project Settings.

#include "SPickupHoverWidget.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Text/STextBlock.h"
#include "Engine/Texture2D.h"
// ------------
#include "BattlegroundStyles.h"


void SPickupHoverWidget::Construct(const FArguments& InArgs)
{
    FSlateFontInfo normalFont = FCoreStyle::Get().GetFontStyle("NormalFont");
    FSlateFontInfo largeFont = FCoreStyle::Get().GetFontStyle("BoldFont");
    normalFont.Size = 15;
    largeFont.Size = 20;

    ChildSlot
        [
            SNew(SBox)
                .HAlign(HAlign_Left)   // center horizontally on screen
                .VAlign(VAlign_Center)   // center vertically on screen
                .Padding(15.f)
                [
                    SNew(SBorder)
                        .BorderBackgroundColor(FLinearColor(0.f, 0.f, 0.f, 0.6f)) // dark 60% opacity
                        .Padding(15.f)
                        .BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox")) // needed for background + radius
                        [
                            SNew(SBox)
                                .MaxDesiredWidth(500.f)    // like max-width: 500px
                                .MaxDesiredHeight(400.f)   // like max-height: 400px
                                .HAlign(HAlign_Center)
                                .VAlign(VAlign_Center)
                                [
                                    SNew(SVerticalBox)

                                        + SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Center)
                                        [
                                            SAssignNew(this->PickupIconImage, SImage).DesiredSizeOverride(FVector2D(100, 100))
                                        ]

                                        + SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Center).Padding(0, 5, 0, 0)
                                        [
                                            SAssignNew(this->PickupText, STextBlock).Font(largeFont).Text(FText::FromString("Item Name"))
                                        ]

                                        + SVerticalBox::Slot()
                                        .AutoHeight()
                                        .HAlign(HAlign_Center)
                                        [
                                            SNew(STextBlock).Text(FText::FromString("Press E to pick up")).Font(normalFont)
                                        ]
                                ]
                        ]
                ]
        ];
}


void SPickupHoverWidget::SetItemData(UTexture2D* itemIcon, const FText& itemName)
{
    if (this->PickupIconImage.IsValid() && itemIcon) this->PickupIconImage->SetImage(WidgetHelpers::FSlateBrushFromTexture(itemIcon));
    if (this->PickupText.IsValid()) this->PickupText->SetText(itemName);
}
