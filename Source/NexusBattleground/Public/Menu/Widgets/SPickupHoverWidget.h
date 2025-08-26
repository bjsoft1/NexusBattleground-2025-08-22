#pragma once

#include "CoreMinimal.h"
#include "SBattlegroundWidget.h"


class NEXUSBATTLEGROUND_API SPickupHoverWidget : public SBattlegroundWidget
{
public:
#pragma region Constructors and Overrides
    SLATE_BEGIN_ARGS(SPickupHoverWidget) {}
    SLATE_ARGUMENT(EAnimationTypes, AnimationType)
    SLATE_END_ARGS()

    void Construct(const FArguments& args);
#pragma endregion Constructors and Overrides


private:
#pragma region Components
    TSharedPtr<SImage> PickupIconImage;
    TSharedPtr<STextBlock> PickupText;
#pragma endregion Components


public:
#pragma region Public Methods
    void SetItemData(UTexture2D* itemIcon, const FText& itemName);
#pragma endregion Public Methods

};
