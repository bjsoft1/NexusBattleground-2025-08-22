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
	const FName BORDER_NEXUS_TEMPLATE_LOGO("Border.NexusTemplateLogo");
	const FName BORDER_PROGRESS("Border.Progress_");
	const FName BORDER_PROGRESS_00("Border.Progress_00");
	const FName BORDER_PROGRESS_10("Border.Progress_10");
	const FName BORDER_PROGRESS_20("Border.Progress_20");
	const FName BORDER_PROGRESS_30("Border.Progress_30");
	const FName BORDER_PROGRESS_40("Border.Progress_40");
	const FName BORDER_PROGRESS_50("Border.Progress_50");
	const FName BORDER_PROGRESS_60("Border.Progress_60");
	const FName BORDER_PROGRESS_70("Border.Progress_70");
	const FName BORDER_PROGRESS_80("Border.Progress_80");
	const FName BORDER_PROGRESS_90("Border.Progress_90");
	const FName BORDER_PROGRESS_100("Border.Progress_100");
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