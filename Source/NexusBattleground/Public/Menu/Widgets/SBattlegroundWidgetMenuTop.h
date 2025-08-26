// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"


class NEXUSBATTLEGROUND_API SBattlegroundWidgetMenuTop : public SCompoundWidget
{

#pragma region Constructors and Overrides
    SLATE_BEGIN_ARGS(SBattlegroundWidgetMenuTop) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& args);
#pragma endregion Constructors and Overrides


private:
#pragma region Components
	TSharedPtr<STextBlock> PlayerNameTextBlock;
	TSharedPtr<STextBlock> PlayerLevelTextBlock;
	TSharedPtr<STextBlock> PlayerScoreIndicatorTextBlock;
	TSharedPtr<SImage> PlayerLevelIndicatorImage;
#pragma endregion Components


private:
#pragma region Configurable & Internal Properties
#pragma endregion Configurable & Internal Properties



public:
#pragma region Public Methods
	void RefreshPlayerInfo(UWorld* world);
#pragma region Public Methods


};