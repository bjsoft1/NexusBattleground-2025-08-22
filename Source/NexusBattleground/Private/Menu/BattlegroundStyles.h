#pragma once
#include "CoreMinimal.h"

namespace WidgetHelpers
{
	static inline FSlateBrush* FSlateBrushFromTexture(UTexture2D* texture)
	{
		FSlateBrush* brush = new FSlateBrush();
		brush->SetResourceObject(texture);
		return brush;
	}
};

namespace WidgetKeys
{
	const FName WIDGET_STYLE_KEY("BattlegroundStyle");

	const FName FONT_LARGE_TITLE("FontKey.LargeTitle");
	const FName FONT_Medium_TITLE("FontKey.MediumTitle");
	const FName FONT_NORMAL_BUTTON("FontKey.NormalButtonfont");
	const FName FONT_HOVER_BUTTON("FontKey.HoverButtonfont");
	const FName FONT_ACTIVE_BUTTON("FontKey.ActiveButtonfont");

	const FName BORDER_SIDE_FADE("Border.SideFade");
};

class FBattlegroundStyles
{
public:
	static void Initialize();
	static void Shutdown();
	static const ISlateStyle& Get();

	FORCEINLINE static const FTextBlockStyle* GetTextBlockStyle(FName styleName) { return &Get().GetWidgetStyle<FTextBlockStyle>(styleName); }
	FORCEINLINE static const FSlateBrush* GetBrushStyle(FName styleName) { return Get().GetBrush(styleName); }

private:
	static TSharedRef<FSlateStyleSet> Create();
	static TSharedPtr<FSlateStyleSet> StyleInstance;
};