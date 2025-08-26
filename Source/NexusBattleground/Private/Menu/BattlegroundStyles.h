#pragma once
#include "CoreMinimal.h"
#include "BattlegroundUtilities.h"

enum class EButtonTypes : uint8;

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

	const FName BORDER_BUTTON_BACKGROUND("Border.ButtonBackground");
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

	const FName SCROLL_DEFAULT("Scroll.Default");

	FORCEINLINE FName GetProgressBorderKey(uint8 progressPercentage)
	{
		int32 LevelStep = (progressPercentage / 10) * 10;
		return FName(*FString::Printf(TEXT("%s%02d"), *BORDER_PROGRESS.ToString(), LevelStep));
	}

};

class FBattlegroundStyles
{
public:
	static void Initialize();
	static void Shutdown();
	static const ISlateStyle& Get();

private:
	static TSharedRef<FSlateStyleSet> Create();
	static TSharedPtr<FSlateStyleSet> StyleInstance;
};

namespace SlateHelpers
{
	const FLinearColor BLACK_COLOR = FLinearColor(0.0f, 0.0f, 0.0f, 1.f);
	const FLinearColor WHITE_COLOR = FLinearColor(1.0f, 1.0f, 1.0f, 1.f);
	const FLinearColor NORMAL_BUTTON_COLOR = FLinearColor(0.1f, 0.1f, 0.1f, 1.f);
	const FLinearColor ACTIVE_BUTTON_COLOR = FLinearColor(0.2196f, 0.5725f, 0.8980f, 1.f);
	const FLinearColor HOVER_BUTTON_COLOR = FLinearColor(0.1196f, 0.3725f, 0.5980f, 1.f);
	const FLinearColor CLICK_BUTTON_COLOR = FLinearColor(0.596f, 0.2725f, 0.4980f, 1.f);
	FORCEINLINE static const FTextBlockStyle* GetTextBlockStyle(FName styleName) { return &FBattlegroundStyles::Get().GetWidgetStyle<FTextBlockStyle>(styleName); }
	FORCEINLINE static const FSlateBrush* GetBrushStyle(FName styleName) { return FBattlegroundStyles::Get().GetBrush(styleName); }
	
	FORCEINLINE static void MakeRoundBrush(FSlateBrush& brush, FLinearColor color)
	{
		const FVector4 radius = FVector4(5.0f, 5.0f, 5.0f, 5.0f);
		brush.TintColor = color;
		brush.DrawAs = ESlateBrushDrawType::Type::RoundedBox;
		brush.OutlineSettings.RoundingType = ESlateBrushRoundingType::Type::FixedRadius;
		brush.OutlineSettings.CornerRadii = radius;
		brush.OutlineSettings.Color = color;
		brush.OutlineSettings.Width = 0.0f;
	}

	FORCEINLINE static const FButtonStyle& GetButtonStyle(EButtonTypes buttonType)
	{
		FButtonStyle* buttonStyle = new FButtonStyle();
		const ESlateBrushRoundingType::Type rounding = ESlateBrushRoundingType::Type::FixedRadius;

		FLinearColor normalColor;
		FLinearColor hoveredColor;
		FLinearColor clickedColor;

		switch (buttonType)
		{
		case EButtonTypes::Menu_Normal:
			normalColor = NORMAL_BUTTON_COLOR;
			hoveredColor = FLinearColor(0.1f, 0.1f, 0.1f, 1.0f);
			clickedColor = CLICK_BUTTON_COLOR;
			break;

		case EButtonTypes::Menu_Active:
			normalColor = FLinearColor(0.2196f, 0.5725f, 0.8980f, 1.f);
			hoveredColor = ACTIVE_BUTTON_COLOR;
			clickedColor = ACTIVE_BUTTON_COLOR;

			break;

		default:
			normalColor = NORMAL_BUTTON_COLOR;
			hoveredColor = HOVER_BUTTON_COLOR;
			clickedColor = CLICK_BUTTON_COLOR;
			break;

		}

		auto normalBrush = new FSlateBrush(*GetBrushStyle(WidgetKeys::BORDER_BUTTON_BACKGROUND));
		auto hoverBrush = new FSlateBrush(*GetBrushStyle(WidgetKeys::BORDER_BUTTON_BACKGROUND));
		auto clickBrush = new FSlateBrush(*GetBrushStyle(WidgetKeys::BORDER_BUTTON_BACKGROUND));
		MakeRoundBrush(*normalBrush, normalColor);
		MakeRoundBrush(*hoverBrush, hoveredColor);
		MakeRoundBrush(*clickBrush, clickedColor);

		buttonStyle->SetNormal(*normalBrush);
		buttonStyle->SetHovered(*hoverBrush);
		buttonStyle->SetPressed(*clickBrush);

		return *buttonStyle;
	}

	FORCEINLINE static const TSharedRef<SButton> CreateMenuButton(TSharedPtr<SButton>& btnRef, const FText& buttonText, EButtonTypes buttonType)
	{
		return SAssignNew(btnRef, SButton).ContentPadding(FMargin(15.0f)).ButtonStyle(&SlateHelpers::GetButtonStyle(buttonType))
			[
				SNew(STextBlock).Text(buttonText).Justification(ETextJustify::Left).TextStyle(GetTextBlockStyle(WidgetKeys::FONT_NORMAL_BUTTON))
					.ColorAndOpacity(FLinearColor(0.8f, 0.8f, 0.8f, 1.0f))
			];
	}
	
};
