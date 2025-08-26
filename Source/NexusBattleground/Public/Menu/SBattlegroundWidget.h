#pragma once
#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "BattlegroundUtilities.h"


class NEXUSBATTLEGROUND_API SBattlegroundWidget : public SCompoundWidget
{

#pragma region Events | Delegates
	DECLARE_DELEGATE(FOnHidden);
#pragma endregion Events | Delegates


public:
#pragma region Public Methods
	virtual void OverrideVisibility(bool isShow, bool newAnimation = false);
	FOnHidden OnHidden;
#pragma endregion Public Methods


private:
#pragma region Configurable & Internal Properties
	EAnimationTypes AnimationType;
	EWidgetStates WidgetState = EWidgetStates::Idle;
	float CurrentAnimation = 0.f;
#pragma endregion Configurable & Internal Properties


protected:
#pragma region Lifecycle Overrides
	virtual void Tick(const FGeometry& allottedGeometry, const double currentTime, const float deltaTime) override;
	virtual void DestroyWidget() = 0;

#pragma endregion Lifecycle Overrides


public:
#pragma region Public Inline Methods
	FORCEINLINE EWidgetStates GetWidgetState() const { return this->WidgetState; }
	FORCEINLINE EAnimationTypes GetAnimationType() const { return this->AnimationType; }
	FORCEINLINE void SetAnimationType(EAnimationTypes animationType) { this->AnimationType = animationType; }
#pragma endregion Public Inline Methods


#pragma region Private Helper Methods
	void UpdateAnimation();
#pragma endregion Private Helper Methods

};
