// Fill out your copyright notice in the Description page of Project Settings.

#pragma region Default System Header Files
#include "SBattlegroundWidget.h"
#pragma endregion Default System Header Files


#pragma region Public Methods
void SBattlegroundWidget::OverrideVisibility(bool isShow, bool newAnimation)
{
    this->CurrentAnimation = (SWidget::RenderOpacity != 0.0f && SWidget::RenderOpacity != 1.0f && !newAnimation)  ? SWidget::RenderOpacity : 0.0f;
    if (isShow)
    {
        if (this->WidgetState == EWidgetStates::AnimatingIn) return;

        SWidget::SetRenderOpacity(this->CurrentAnimation);
        SWidget::SetVisibility(EVisibility::Visible);
        this->WidgetState = EWidgetStates::AnimatingIn;
    }
    else
    {
        this->WidgetState = EWidgetStates::AnimatingOut;
        if (SWidget::GetVisibility() != EVisibility::Visible)
        {
            this->CurrentAnimation = 1.0f;
            return;
        }
    }
}
#pragma endregion Public Methods


#pragma region Lifecycle Overrides
void SBattlegroundWidget::Tick(const FGeometry& allottedGeometry, const double currentTime, const float deltaTime)
{
    if (this->WidgetState == EWidgetStates::Idle) return;

    this->UpdateAnimation();
}
#pragma endregion Lifecycle Overrides


#pragma region Private Helper Methods
void SBattlegroundWidget::UpdateAnimation()
{
    const float animationSpeed = 6.f;
    this->CurrentAnimation += animationSpeed * FApp::GetDeltaTime();
    const bool isOut = this->WidgetState == EWidgetStates::AnimatingOut;

    if (this->CurrentAnimation >= 1.f)
    {
        this->CurrentAnimation = 1.f;

        if (isOut)
        {
            SWidget::SetVisibility(EVisibility::Collapsed);
            OnHidden.ExecuteIfBound();
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
#pragma endregion Private Helper Methods
