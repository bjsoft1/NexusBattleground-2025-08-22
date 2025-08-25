#pragma once
#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "BattlegroundUtilities.h"

DECLARE_DELEGATE(FOnRequestDestroy);

class NEXUSBATTLEGROUND_API SBattlegroundWidget : public SCompoundWidget
{
public:
	void ConstructBase(EAnimationTypes animationType)
	{
		this->AnimationType = animationType;
	}

	virtual void OverrideVisibility(bool isShow, bool autoDestroy = false);
	FOnRequestDestroy OnRequestDestroy;

private:
	EAnimationTypes AnimationType;
	EWidgetStates WidgetState = EWidgetStates::Idle;
	float CurrentAnimation = 0.f;

	virtual void Tick(const FGeometry& allottedGeometry, const double currentTime, const float deltaTime) override;
	void UpdateAnimation();

	FORCEINLINE EWidgetStates GetWidgetState() const { return this->WidgetState; }
	FORCEINLINE EAnimationTypes GetAnimationType() const { return this->AnimationType; }
};
