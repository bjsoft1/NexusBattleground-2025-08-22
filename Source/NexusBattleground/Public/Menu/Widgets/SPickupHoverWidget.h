#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class NEXUSBATTLEGROUND_API SPickupHoverWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SPickupHoverWidget) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& inArgs);
    void SetItemData(UTexture2D* itemIcon, const FText& itemName);

private:
    TSharedPtr<SImage> PickupIconImage;
    TSharedPtr<STextBlock> PickupText;
};
