#pragma once

#include "CoreMinimal.h"
#include "SBattlegroundWidget.h"


class NEXUSBATTLEGROUND_API SPickupHoverWidget : public SBattlegroundWidget
{
public:
    SLATE_BEGIN_ARGS(SPickupHoverWidget) {}
    SLATE_ARGUMENT(EAnimationTypes, AnimationType)
    SLATE_END_ARGS()

    void Construct(const FArguments& args);
    void SetItemData(UTexture2D* itemIcon, const FText& itemName);

    TSharedPtr<SImage> PickupIconImage;
    TSharedPtr<STextBlock> PickupText;
};
