// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "BattlegroundUtilities.h"
#include "GameFramework/Actor.h"
#include "BattlegroundPickup.generated.h"


#pragma region Forward declaretions
#pragma endregion Forward declaretions


UCLASS()
class NEXUSBATTLEGROUND_API ABattlegroundPickup : public AActor
{
	GENERATED_BODY()


#pragma region Friend Declarations
#pragma endregion Friend Declarations

public:
#pragma region Constructors and Overrides
	ABattlegroundPickup(const FObjectInitializer& objectInitializer);
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
#pragma endregion Constructors and Overrides


protected:
#pragma region Lifecycle Overrides
	virtual void BeginPlay() override;
	/**
	* EndPlay override for ABattlegroundPickup.
	*
	* Since PickupMesh is dynamically created on the client side (not on the server),
	* we need to explicitly destroy it when the actor is ending play.
	*
	* Destroying the component here ensures:
	*   1. Memory is properly released and garbage collected.
	*   2. No dangling pointers remain (we set PickupMesh = nullptr).
	*   3. Multiplayer safety: only client-side visuals are affected; server and other clients remain unaffected.
	*
	* This is a clean, professional approach to handle dynamically created components.
	*/
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;
#pragma endregion Lifecycle Overrides


protected:
#pragma region Components
	UPROPERTY() UStaticMeshComponent* PickupMesh;
#pragma endregion Components


private:
#pragma region Configurable & Internal Properties
	UPROPERTY(Replicated) uint16 PickupAmount;
	UPROPERTY(ReplicatedUsing = OnRep_DatatableRowId) FName DatatableRowId;
	UPROPERTY() FPickupData PickupData;
	UPROPERTY() EPickupTypes PickupType;
	UPROPERTY() uint8 PickupSubType;
#pragma endregion Configurable & Internal Properties


public:
#pragma region Public Inline Methods
	FORCEINLINE void InitializePickup(const FName& rowId, uint16 amount = 1)
	{
		if (AActor::HasAuthority())
		{
			this->DatatableRowId = rowId;
			this->PickupAmount = amount;

			if (BattlegroundUtilities::IsListenServer(GetWorld())) OnRep_DatatableRowId();

			float offsetZ = 0.f;
			if (this->PickupData.PickupType == EPickupTypes::Ammo) offsetZ = 0.f;
			else if (this->PickupData.PickupType == EPickupTypes::Sight) offsetZ = 0.f;
			else if (this->PickupData.PickupType == EPickupTypes::Armor) offsetZ = 0.f;
			else if (this->PickupData.PickupType == EPickupTypes::Medkit) offsetZ = 0.f;
			else if (this->PickupData.PickupType == EPickupTypes::Helmet) offsetZ = 25.f;
			else if (this->PickupData.PickupType == EPickupTypes::Weapon) offsetZ = 13.f;
			else if (this->PickupData.PickupType == EPickupTypes::Backpack) offsetZ = 0.f;


			if (offsetZ != 0.0f)
			{
				FVector location = AActor::GetActorLocation();
				location.Z += offsetZ;
				AActor::SetActorLocation(location);
			}
		}
	}
#pragma endregion Public Inline Methods


public:
#pragma region Public Methods
	/**
	 * Highlights the pickup item by enabling a post-process outline.
	 *
	 * @param isHighlight  Whether to enable (true) or disable (false) the highlight.
	 *
	 * How it works:
	 *   - If the player looks at the pickup from nearby, this function highlights the outline to make it easily visible.
	 *   - Ready for pickup indication.
	 *   - The function only works if a PostProcessVolume exists in the map:
	 *       Name: PostProcessVolume_Outline
	 *       Rendering Features > Post Process Materials > Array index 0 -> Selected PP_Outliner_Inst
	 *
	 * Example setup guide:
	 *   Youtube: #YOUTUBE_HOW_TO_SETUP_OUTLINER
	 *
	 * UE Macro tip:
	 *   You can use UE_MICRO for quick in-code reference or documentation flags.
	 */
	void SetHighlight(bool isHighlight);
#pragma endregion Public Methods


protected:
#pragma region Protected Methods
#pragma endregion Protected Methods


private:
#pragma region Private Helper Methods
#pragma endregion Private Helper Methods


private:
#pragma region Input Bindings
#pragma endregion Input Bindings

private:
#pragma region Callbacks
#pragma endregion Callbacks


private:
#pragma region Server/Multicast RPC
#pragma endregion Server/Multicast RPC


private:
#pragma region Client/OnRep RPC
	UFUNCTION() void OnRep_DatatableRowId();
#pragma endregion Client/OnRep RPC


private:
#pragma region Debug Methods
#pragma endregion Debug Methods


public:
#pragma region Delegates
#pragma endregion Delegates

};
