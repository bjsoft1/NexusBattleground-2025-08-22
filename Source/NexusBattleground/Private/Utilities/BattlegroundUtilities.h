#pragma once
#include "BattlegroundStruct.h"

// Declare custom log category
DECLARE_LOG_CATEGORY_EXTERN(LogNexus, Log, All);

#ifndef DEFAULT_MAX_WALK_SPEED
#define DEFAULT_MAX_WALK_SPEED 450.0f
#define DEFAULT_MAX_CROUCHED_WALK_SPEED 350.0f
#define DEFAULT_CAPSULE_HALF_HEIGHT 90.0f
#define CROUCH_CAPSULE_HALF_HEIGHT 60.0f

#define HEAD_CAMERA_SOCKET FName("headCameraSocket")

#define ROOT_PATH(relativePath) TEXT("/Game/") relativePath
#define ASSET_PATH(relativePath) TEXT("/Game/NexusBattleground/") relativePath

#define NEXUS_INFO(Format, ...)    UE_LOG(LogNexus, Log, TEXT(Format), ##__VA_ARGS__)
#define NEXUS_WARNING(Format, ...) UE_LOG(LogNexus, Warning, TEXT(Format), ##__VA_ARGS__)
#define NEXUS_ERROR(Format, ...)   UE_LOG(LogNexus, Error, TEXT(Format), ##__VA_ARGS__)

#endif

static class AssetsPaths
{
public:
	static const FString SKM_FEMALE_PATH;
	static const FString SKM_MALE_PATH;

	static const FString ANIM_FEMALE_PATH;
	
	static const FString CLS_PICKUP_MANAGER_PATH;
};

static class BattlegroundUtilities
{
public:
	static bool ParsePickupRowName(const FName& rowName, EPickupTypes& outPickupType, uint8& outSubType)
	{
		FString rowString = rowName.ToString();
		TArray<FString> parts;
		rowString.ParseIntoArray(parts, TEXT("_"), true);

		if (parts.Num() != 2) return false;

		FString typeString = parts[0];
		outPickupType = EPickupTypes::Ammo;


		for (uint8 i = 0; i < static_cast<int32>(6u) + 1u; i++)
		{
			FString enumString = UEnum::GetValueAsString(static_cast<EPickupTypes>(i));
			enumString = enumString.RightChop(enumString.Find(TEXT("::")) + 2);
			if (enumString.Equals(typeString, ESearchCase::IgnoreCase))
			{
				outPickupType = static_cast<EPickupTypes>(i);
				break;
			}
		}
		outSubType = FCString::Atoi(*parts[1]);
		return true;
	}
};