// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBattlegroundWidget.h"

#pragma region Forward Declarations
class SBattlegroundWidgetMenuTop;
enum class EChildrenMenus : uint8;
#pragma endregion Forward Declarations


struct FChildrenMenu
{
	EChildrenMenus MenuType;
	TSharedPtr<SBattlegroundWidget> ChildWidget;
};

class NEXUSBATTLEGROUND_API SBattlegroundMenu : public SBattlegroundWidget
{

public:
#pragma region Constructors and Overrides
    SLATE_BEGIN_ARGS(SBattlegroundMenu) {}
        SLATE_ARGUMENT(EAnimationTypes, AnimationType)
		SLATE_ARGUMENT(UWorld*, World)
    SLATE_END_ARGS()

    void Construct(const FArguments& args);
#pragma endregion Constructors and Overrides


private:
#pragma region Components
	UWorld* world;
	TSharedPtr<SBattlegroundWidgetMenuTop> MenuTopWidget;
	TArray<FChildrenMenu> ChildrenMenus;

    // -------------
    TSharedPtr<SImage> PickupIconImage;
    TSharedPtr<STextBlock> PickupText;
#pragma endregion Components


public:
#pragma region Public Methods
	FORCEINLINE UWorld* GetWorld() const { return this->world; }
#pragma region Public Methods


#pragma region Private Helper Methods
	//TSharedPtr<SBattlegroundWidget> GetChildWidget(EChildrenMenus menuType);
    //TSharedPtr<SBattlegroundWidget> CreateChildWidget(EChildrenMenus menuType);
    //TSharedPtr<SBattlegroundWidget> GetOrCreateChildWidget(EChildrenMenus menuType);

#pragma endregion Private Helper Methods


#pragma region Callbacks
	UFUNCTION() void OnSettingsUpdated(ESaveGameTypes type);
#pragma endregion Callbacks
};
