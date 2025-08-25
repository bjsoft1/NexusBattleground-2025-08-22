#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

DECLARE_DELEGATE(FOnRequestDestroy);

enum class EAnimationTypes : uint8
{
    None = 0,
    FadeIn_Out = 1,
    MoveLeft_Right = 2,
};
enum class EWidgetStates : uint8
{
    Idle = 0,
    AnimatingIn = 1,
    AnimatingOut = 2,
    AnimatingOut_AutoDestroy = 3
};

class NEXUSBATTLEGROUND_API SPickupHoverWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SPickupHoverWidget) {}
    SLATE_ARGUMENT(EAnimationTypes, AnimationType)
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);
    void SetItemData(UTexture2D* itemIcon, const FText& itemName);
    virtual void OverrideVisibility(bool isShow, bool autoDestroy = false);
    FOnRequestDestroy OnRequestDestroy;

private:
    EAnimationTypes AnimationType;
    EWidgetStates WidgetState = EWidgetStates::Idle;
	float CurrentAnimation = 0.f;

    virtual void Tick(const FGeometry& allottedGeometry, const double currentTime, const float deltaTime) override;
    void UpdateAnimation();
    TSharedPtr<SImage> PickupIconImage;
    TSharedPtr<STextBlock> PickupText;
};
