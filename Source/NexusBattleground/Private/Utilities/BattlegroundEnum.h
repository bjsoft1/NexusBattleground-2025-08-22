#pragma once
#include "CoreMinimal.h"

enum class ECameraModes : uint8
{
	CM_FirstPerson = 0,
	CM_SecondPerson = 1,
	CM_ThirdPerson = 2,
};

UENUM(BlueprintType)
enum class EAnimationOffsets : uint8
{
	AO_UnarmedStand UMETA(DisplayName = "Unarmed Stand"),
	AO_UnarmedCrouch UMETA(DisplayName = "Unarmed Crouch"),

	AO_ArmedStand UMETA(DisplayName = "Armed Stand"),
	AO_ArmedCrouch UMETA(DisplayName = "Armed Crouch"),

	AO_ArmedAimStand UMETA(DisplayName = "Armed Aim Stand"),
	AO_ArmedAimCrouch UMETA(DisplayName = "Armed Aim Crouch"),
};


//UENUM(BlueprintType)
//enum class EWeaponTypes : uint8
//{
//	WT_None UMETA(DisplayName = "None"),
//	WT_Pistol UMETA(DisplayName = "Pistol"),
//	WT_Rifle UMETA(DisplayName = "Rifle"),
//	WT_Shotgun UMETA(DisplayName = "Shotgun"),
//	WT_Sniper UMETA(DisplayName = "Sniper"),
//};
