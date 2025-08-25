// Fill out your copyright notice in the Description page of Project Settings.

#include "SPickupHoverWidget.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Text/STextBlock.h"
#include "Engine/Texture2D.h"
// ------------
#include "BattlegroundStyles.h"


void SPickupHoverWidget::Construct(const FArguments& InArgs)
{
    AnimationType = InArgs._AnimationType;

    FSlateFontInfo normalFont = FCoreStyle::Get().GetFontStyle("NormalFont");
    FSlateFontInfo largeFont = FCoreStyle::Get().GetFontStyle("BoldFont");
    normalFont.Size = 15;
    largeFont.Size = 20;

    ChildSlot
        [
            SNew(SBox).HAlign(HAlign_Left).VAlign(VAlign_Fill)
                [
                    SNew(SBorder).BorderBackgroundColor(FLinearColor(0.f, 0.f, 0.f, 0.6f)) // dark 60% opacity
                        .Padding(30.f)
                        .BorderImage(FBattlegroundStyles::GetBrushStyle(WidgetKeys::BORDER_SIDE_FADE))
                        [
                            SNew(SBox)
                                .MaxDesiredWidth(600.f)    // like max-width: 500px
                                .MaxDesiredHeight(500.f)   // like max-height: 400px
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

void SPickupHoverWidget::OverrideVisibility(bool isShow, bool autoDestroy)
{
    this->CurrentAnimation = (SWidget::RenderOpacity != 0.0f && SWidget::RenderOpacity != 1.0f) ? SWidget::RenderOpacity : 0.0f;
    if (isShow)
    {
        if (this->WidgetState == EWidgetStates::AnimatingIn) return;

        SWidget::SetRenderOpacity(this->CurrentAnimation);
        SWidget::SetVisibility(EVisibility::Visible);
        this->WidgetState = EWidgetStates::AnimatingIn;
    }
    else
    {
        this->WidgetState = autoDestroy ? EWidgetStates::AnimatingOut_AutoDestroy : EWidgetStates::AnimatingOut;
        if (SWidget::GetVisibility() != EVisibility::Visible)
        {
            this->CurrentAnimation = 1.0f;
            return;
        }
    }
}

void SPickupHoverWidget::Tick(const FGeometry& allottedGeometry, const double currentTime, const float deltaTime)
{
    if (this->WidgetState == EWidgetStates::Idle) return;

	this->UpdateAnimation();
}

void SPickupHoverWidget::UpdateAnimation()
{
    const float animationSpeed = 6.f;
    this->CurrentAnimation += animationSpeed * FApp::GetDeltaTime();
    const bool isOut = this->WidgetState == EWidgetStates::AnimatingOut || this->WidgetState == EWidgetStates::AnimatingOut_AutoDestroy;

    if (this->CurrentAnimation >= 1.f)
    {
        this->CurrentAnimation = 1.f;

        if (isOut)
        {
            SWidget::SetVisibility(EVisibility::Collapsed);
            if (this->WidgetState == EWidgetStates::AnimatingOut_AutoDestroy) OnRequestDestroy.ExecuteIfBound();
        }

        this->WidgetState = EWidgetStates::Idle;
    }

    SWidget::SetRenderOpacity(isOut ? (1.0f - this->CurrentAnimation) : this->CurrentAnimation);
}
