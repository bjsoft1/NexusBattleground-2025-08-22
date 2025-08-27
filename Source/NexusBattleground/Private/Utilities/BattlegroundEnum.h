#pragma once
#include "CoreMinimal.h"
#include "BattlegroundEnum.generated.h"

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

UENUM(BlueprintType)
enum class EWeaponTypes : uint8
{
	WT_None UMETA(DisplayName = "None"),
	WT_Knife UMETA(DisplayName = "Knife"),
	WT_Pistol UMETA(DisplayName = "Pistol"),
	WT_Shotgun UMETA(DisplayName = "Shotgun"),
	WT_Grenade UMETA(DisplayName = "Grenade"),
	WT_AssaultRifle UMETA(DisplayName = "Assault Rifle"),
	WT_SubmachineGun UMETA(DisplayName = "Submachine Gun"),
};

UENUM(BlueprintType)
enum class EAnimationStates : uint8
{
	None = 0     UMETA(Hidden),
	IsAiming = 1 << 0,
	IsReloading = 1 << 1,
	IsWeaponEquipped = 1 << 2,
	IsPlayingMontage = 1 << 3,
	IsFreeFalling = 1 << 4,
	IsParachuteOpen = 1 << 5,
	IsProne = 1 << 6
};
ENUM_CLASS_FLAGS(EAnimationStates)

UENUM(BlueprintType, meta = (Bitflags))
enum class EGameModes : uint8
{
	/** Battle Royal */
	GM_BR      UMETA(DisplayName = "Battle Royale"),
	/** Capture The Flag */
	GM_CTF     UMETA(DisplayName = "Capture the Flag"),
	/** Development */
	GM_DEV     UMETA(DisplayName = "Development"),
	/** Kill Confirm */
	GM_KC      UMETA(DisplayName = "Kill Confirm"),
	/** Search and Destroy */
	GM_SD      UMETA(DisplayName = "Search Destroy"),
	/** Solo Deathmatch / Free for all */
	GM_SDM     UMETA(DisplayName = "Solo Deathmatch"),
	/** Team Deathmatch */
	GM_TDM     UMETA(DisplayName = "Team Deathmatch"),
	/** Training / School */
	GM_TRN     UMETA(DisplayName = "Training")
};


UENUM(BlueprintType)
enum class EPickupTypes : uint8
{
	Ammo			UMETA(DisplayName = "Ammo"),
	Sight			UMETA(DisplayName = "Sight"),
	Armor			UMETA(DisplayName = "Armor"),
	Medkit			UMETA(DisplayName = "Medkit"),
	Helmet			UMETA(DisplayName = "Helmet"),
	Weapon			UMETA(DisplayName = "Weapon"),
	Backpack		UMETA(DisplayName = "Backpack"),
};

enum class EPickupMedkitTypes : uint8
{
	Bandage = 1,
	FirstAidKit = 2,
	Medkit = 3,
	EnergyDrink = 4,
	Painkiller = 5,
	AdrenalineSyringe = 6,
};

enum EDirections : uint8
{
	Left = 0,
	Right = 1,
	Top = 2,
	Bottom = 3,
	Center = 4
};

enum class EAnimationTypes : uint8
{
	None = 0,
	FadeIn_Out = 1,
	MoveLeft_Right = 2,
};
enum class EWidgetStates : uint8
{
	Idle = 0,
	AnimatingIn = 1,
	AnimatingOut = 2,
};

enum class EChildrenMenus : uint8
{
	MAX = 0,
	AboutGame = 1,
	HostGame = 2,
	JoinGame = 3,
	Inventory = 4,
	DisplaySettings = 5,
	SoundSettings = 6,
	ControlSettings = 7,
	Leaderboard = 8,
	RecordedGame = 9,
	ExitGame = 10,
	BackToGame = 11,
};

enum class ESaveGameTypes : uint8
{
	MAX = 0,
	PlayerData = 1,
	GraphicSettings = 2,
	AudioSettings = 3,
	ControlSettings = 4,
	GameSettings = 5,
};

enum class EButtonTypes : uint8
{
	Default = 0,
	Menu_Normal = 1,
	Menu_Active = 2,
};