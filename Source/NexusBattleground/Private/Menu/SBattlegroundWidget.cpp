// Fill out your copyright notice in the Description page of Project Settings.

#include "SBattlegroundWidget.h"

void SBattlegroundWidget::OverrideVisibility(bool isShow, bool autoDestroy)
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
void SBattlegroundWidget::Tick(const FGeometry& allottedGeometry, const double currentTime, const float deltaTime)
{
    if (this->WidgetState == EWidgetStates::Idle) return;

    this->UpdateAnimation();
}
void SBattlegroundWidget::UpdateAnimation()
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

    if (this->AnimationType == EAnimationTypes::FadeIn_Out) SWidget::SetRenderOpacity(isOut ? (1.0f - this->CurrentAnimation) : this->CurrentAnimation);
    else if (this->AnimationType == EAnimationTypes::MoveLeft_Right)
    {
        const float offsetX = 300.f * (isOut ? -this->CurrentAnimation : (1.0f - this->CurrentAnimation));
        SWidget::SetRenderTransform(FSlateRenderTransform(FVector2D(isOut ? offsetX : -offsetX, 0.f)));
        SWidget::SetRenderOpacity(isOut ? (1.0f - this->CurrentAnimation) : this->CurrentAnimation);
    }
}
