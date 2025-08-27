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

#define DEFAULT_MAIN_MENU_DELAY 0.3f
#define DEFAULT_QUIT_GAME_DELAY 1.0f
#endif

static class AssetsPaths
{
public:
	static const FString DEFAULT_WIDGET_STYLE_PATH;

	static const FString SKM_FEMALE_PATH;
	static const FString SKM_MALE_PATH;

	static const FString ANIM_FEMALE_PATH;
	
	static const FString CLS_PICKUP_MANAGER_PATH;

	static const FString TX2D_MAIN_HUD_PATH;
};

static class BattlegroundUtilities
{
public:

		/**
	* Parses a DataTable row name to extract the PickupType and SubType.
	*
	* Row names are expected in the format: "<PickupTypeEnumName>_<SubType>"
	* For example: "Ammo_1", "Weapon_3", etc.
	*
	* This function:
	* - Splits the row name by underscore ('_')
	* - Maps the first part to the corresponding EPickupTypes enum
	* - Converts the second part to a uint8 SubType
	*
	* @param rowName        The FName of the DataTable row to parse
	* @param outPickupType  Output parameter to receive the parsed EPickupTypes value
	* @param outSubType     Output parameter to receive the parsed sub-type as uint8
	* @return true if parsing succeeded and both PickupType and SubType were valid, false otherwise
	*/
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


	/**
	 * Checks whether the current UWorld is running as a listen server.
	 *
	 * A listen server is a server that also has a local player playing on it.
	 * This is useful to handle cases where OnRep functions won't trigger for
	 * the host player, since replication notifications only fire on remote clients.
	 *
	 * @param world - The UWorld context to check.
	 * @return true if this instance is a listen server, false otherwise.
	 */
	FORCEINLINE static bool IsListenServer(const UWorld* world)
	{
		return world && world->GetNetMode() == NM_ListenServer;
	}

	static class UBattlegroundSettingsManager* GetSettingsManager(const UWorld* world);

	static void SetUpdateMouseFocus(UWorld* world, bool isMenu, bool isNeedMouseEvent = true);

	FORCEINLINE static bool IsStaticMeshPickup(const FName& rowName)
	{
		return !rowName.ToString().StartsWith("Weapon_");
	}
	FORCEINLINE static bool IsBackpackPickup(const FName& rowName)
	{
		return rowName.ToString().StartsWith("Backpack_");
	}
	FORCEINLINE static bool IsPickupNeedAttachIntoCharecter(const FName& rowName)
	{
		FString rowString = rowName.ToString();
		return rowString.StartsWith("Helmet_") || rowString.StartsWith("Weapon_") || rowString.StartsWith("Backpack_");
	}
};

static class GameScoreCalculator
{
public:
	static int32 GetScoreForLevel(int32 currentLevel)
	{
		// Base starting score for level 1
		float score = 10.0f;

		// Starting increment percentage (50% for first levels)
		float incrementPercent = 0.5f; // 50%  

		// Decay factor: each level reduces increment percentage
		float decayFactor = 0.95f; // 95% of previous increment

		for (int32 i = 1; i < currentLevel; i++)
		{
			// Increase score by current percentage
			score += score * incrementPercent;

			// Reduce increment percentage for next level
			incrementPercent *= decayFactor;

			// Clamp min increment to 10% for higher levels
			incrementPercent = FMath::Max(incrementPercent, 0.10f);
		}

		return FMath::RoundToInt(score);
	}

	static uint8 GetLevelCompletionPercent(int32 levelScore, int32 currentLevel, int32 currentScore)
	{
		const float percentage = (float)currentScore / (float)levelScore * 100.0f;

		if (percentage >= 100.0f) return 100;

		return (uint8)(percentage);
	}
	static uint8 GetLevelCompletionPercent(int32 currentLevel, int32 currentScore)
	{
		const int32 levelScore = GetScoreForLevel(currentLevel);

		const float percentage = (float)currentScore / (float)levelScore * 100.0f;

		if (percentage >= 100.0f) return 100;

		return (uint8)(percentage);
	}
};

namespace BattlegroundKeys
{
	const FString SAVE_GAME_DEFAULT_SLOT = TEXT("PlayerSaveSlot");
}


