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
