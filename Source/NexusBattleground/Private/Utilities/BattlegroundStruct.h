#pragma once

#include "BattlegroundEnum.h"
#include "BattlegroundStruct.generated.h"

USTRUCT(BlueprintType)
struct FPickupData
{
	GENERATED_BODY()

public:
	UPROPERTY() uint8 Quantity = 0;
	UPROPERTY() EPickupTypes PickupType;
	UPROPERTY() uint8 Subtype = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString PickupName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 AffectValue = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 SpaceRequired = 0;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TSoftObjectPtr<UTexture2D> PickIcon = nullptr;
};
