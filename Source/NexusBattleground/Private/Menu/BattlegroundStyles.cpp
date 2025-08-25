#include "BattlegroundStyles.h"
#include "Styling/SlateStyleRegistry.h"
#include "Brushes/SlateDynamicImageBrush.h"
#include "Engine/Texture2D.h"
#include "Slate/SlateGameResources.h"
//---------------------
#include "BattlegroundUtilities.h"

TSharedPtr<FSlateStyleSet> FBattlegroundStyles::StyleInstance = nullptr;

void FBattlegroundStyles::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FBattlegroundStyles::Shutdown()
{
	if (StyleInstance.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
		StyleInstance.Reset();
	}
}



/**
 * Slate Style Macros
 *
 * These helper macros make it easier and cleaner to load Slate UI resources (images, boxes, and fonts)
 * from the project's content directory. Instead of writing the full path and boilerplate every time,
 * you can use these short macros to define brushes and fonts consistently.
 *
 * - SLATE_ROOT_PATH:
 *   Defines the base folder path for all Slate assets. Currently set to:
 *   ProjectContentDir()/NexusBattleground/Assets/SlateWidget
 *
 * - IMAGE_BRUSH(RelativePath, ...):
 *   Loads an image (.png) from the "Icons" subfolder.
 *   Example: IMAGE_BRUSH("PlayButton", FVector2D(32,32))
 *   → Loads NexusBattleground/Assets/SlateWidget/Icons/PlayButton.png
 *
 * - BOX_BRUSH(RelativePath, ...):
 *   Loads a scalable box image (.png) from the "Boxes" subfolder, typically used for panels or frames.
 *   Example: BOX_BRUSH("PanelBackground", FMargin(4/16.0f))
 *   → Loads NexusBattleground/Assets/SlateWidget/Boxes/PanelBackground.png
 *
 * - TTF_FONT(RelativePath, ...):
 *   Loads a TrueType font (.ttf) from the "Fonts" subfolder with a given size/style.
 *   Example: TTF_FONT("Roboto-Regular", 14)
 *   → Loads NexusBattleground/Assets/SlateWidget/Fonts/Roboto-Regular.ttf at size 14
 *
 * These macros keep your Slate style definitions clean, reduce repetition, and make it easy
 * to organize UI assets by type (Icons, Boxes, Fonts).
 */
#define SLATE_ROOT_PATH FPaths::ProjectContentDir() / "Slate"
#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( SLATE_ROOT_PATH / RelativePath + TEXT(".png"), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( SLATE_ROOT_PATH / RelativePath + TEXT(".png"), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( SLATE_ROOT_PATH / RelativePath + TEXT(".png"), __VA_ARGS__ )
#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( SLATE_ROOT_PATH / "Fonts" / RelativePath + TEXT(".ttf"), __VA_ARGS__ )

PRAGMA_DISABLE_OPTIMIZATION
TSharedRef<FSlateStyleSet> FBattlegroundStyles::Create()
{
	// Create a new Slate style set with the specified name and asset paths
	TSharedRef<FSlateStyleSet> slateStyleSetRef = FSlateGameResources::New(WidgetKeys::WIDGET_STYLE_KEY, AssetsPaths::DEFAULT_WIDGET_STYLE_PATH, AssetsPaths::DEFAULT_WIDGET_STYLE_PATH);
	FSlateStyleSet& slateStyleSet = slateStyleSetRef.Get();


	// LARGE TITLE FONT
	slateStyleSet.Set(WidgetKeys::FONT_LARGE_TITLE, FTextBlockStyle().SetFont(TTF_FONT("Roboto-Black", 25))
		.SetColorAndOpacity(FLinearColor::White).SetShadowOffset(FIntPoint(-1, 1)));

	// MEDIUM TITLE FONT
	slateStyleSet.Set(WidgetKeys::FONT_Medium_TITLE, FTextBlockStyle().SetFont(TTF_FONT("Roboto-Bold", 20))
		.SetColorAndOpacity(FLinearColor::White).SetShadowOffset(FIntPoint(-1, 1)));

	// NORMAL BUTTON FONT
	slateStyleSet.Set(WidgetKeys::FONT_NORMAL_BUTTON, FTextBlockStyle().SetFont(TTF_FONT("Roboto-Regular", 18))
		.SetColorAndOpacity(FLinearColor::White).SetShadowOffset(FIntPoint(-1, 1)));

	// HOVER BUTTON FONT
	slateStyleSet.Set(WidgetKeys::FONT_HOVER_BUTTON, FTextBlockStyle().SetFont(TTF_FONT("Roboto-Regular", 18))
		.SetColorAndOpacity(FLinearColor::Yellow).SetShadowOffset(FIntPoint(-1, 1)));
	
	// ACTIVE BUTTON FONT
	slateStyleSet.Set(WidgetKeys::FONT_ACTIVE_BUTTON, FTextBlockStyle().SetFont(TTF_FONT("Roboto-Medium", 18))
		.SetColorAndOpacity(FLinearColor::Green).SetShadowOffset(FIntPoint(-1, 1)));


	// SIDE BACKGROUND FADE
	slateStyleSet.Set(WidgetKeys::BORDER_SIDE_FADE, new IMAGE_BRUSH("Boxes/Tx_RightFade", FVector2D(256, 256)));

	return slateStyleSetRef;
}
PRAGMA_ENABLE_OPTIMIZATION

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_FONT
#undef SLATE_ROOT_PATH

const ISlateStyle& FBattlegroundStyles::Get()
{
	return *StyleInstance;
}