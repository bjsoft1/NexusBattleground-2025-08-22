#pragma once

#include "BattlegroundEnum.h"
#include "BattlegroundStruct.generated.h"

/**
 * FPickupData
 *
 * Holds all data needed to define a pickup (type, mesh, name, etc.).
 * Uses TSoftObjectPtr for meshes/icons so assets are only loaded when needed.
 * This keeps memory usage low and avoids loading every pickup asset at once.
 * If some pickup already loaded the mesh, it will be reused for other pickups of the same type.
 * So, it auto handle by Unreal Engine, If we use TSoftObjectPtr.
 */
USTRUCT(BlueprintType)
struct FPickupData
{
	GENERATED_BODY()

public:
	UPROPERTY() EPickupTypes PickupType;
	UPROPERTY() uint8 Subtype = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool IsValid = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString PickupName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 AffectValue = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 SpawnChance = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float DefaultScale = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName RowName;

	/**
	 * Skeletal mesh for the pickup item.
	 *
	 * We use TSoftObjectPtr here to reference assets lazily. This allows:
	 *   - Avoid loading all 1000+ meshes into memory at once.
	 *   - Only load the asset when the pickup is spawned in the level.
	 *   - Avoid duplicating memory if multiple pickups use the same mesh.
	 *
	 * Example: If 50 AK47 pickups exist on the ground:
	 *   - Each pickup references the same TSoftObjectPtr.
	 *   - When spawning, LoadSynchronous() loads the AK47 mesh once.
	 *   - All 50 pickups share the same UStaticMesh in memory.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TSoftObjectPtr<USkeletalMesh> SkeletalMesh = nullptr;

	/**
	* Static mesh for the pickup item.
	*
	* Same benefits as SkeletalMesh:
	*   - Lazy loading.
	*   - Memory efficient.
	*   - Shared among pickups that use the same mesh.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TSoftObjectPtr< UStaticMesh> StaticMesh = nullptr;

	/**
	 * Icon for the pickup.
	 *
	 * TSoftObjectPtr avoids loading all icons at once.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TSoftObjectPtr<UTexture2D> PickupIcon = nullptr;
};


/**
	* Server doesn’t replicate heavy assets like meshes.
	* Instead, it sends lightweight identifiers (like RowName) to clients.
	*
*/
USTRUCT(BlueprintType)
struct FInventoryServer
{
	GENERATED_BODY()
	UPROPERTY() FName RowName;
	UPROPERTY() FName AttachedSocket;
	UPROPERTY() int32 Quantity = 1;
	UPROPERTY() uint8 Subtype = 1;
	UPROPERTY() EPickupTypes PickupType = EPickupTypes::Unknown;
};


/**
	* Client needs the actual mesh to display the item.
	* It uses the RowName to look up additional data if needed.
*/
USTRUCT(BlueprintType)
struct FInventoryClient
{
	GENERATED_BODY()

	UPROPERTY() FName RowName;
	UPROPERTY() FName AttachedSocket;
	UPROPERTY() USkeletalMesh* SkeletalMesh;
	UPROPERTY() UStaticMesh* StaticMesh;
	UPROPERTY() int32 Quantity = 1;
	UPROPERTY() EPickupTypes PickupType;
	UPROPERTY() uint8 Subtype = 1;
};

