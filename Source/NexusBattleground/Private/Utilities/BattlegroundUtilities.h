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

};

static class BattlegroundStyles
{
public:
	static inline FSlateBrush* FSlateBrushFromTexture(UTexture2D* texture)
	{
		FSlateBrush* brush = new FSlateBrush();
		brush->SetResourceObject(texture);
		return brush;
	}
};