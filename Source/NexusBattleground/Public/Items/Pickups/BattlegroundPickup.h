// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
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
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;
#pragma endregion Lifecycle Overrides


protected:
#pragma region Components
	UStaticMeshComponent* PickupMesh;
#pragma endregion Components


private:
#pragma region Configurable & Internal Properties
	UPROPERTY(Replicated) uint16 PickupAmount;
	UPROPERTY(ReplicatedUsing = OnRep_DatatableRowId) FName DatatableRowId;
#pragma endregion Configurable & Internal Properties


public:
#pragma region Public Inline Methods
#pragma endregion Public Inline Methods


public:
#pragma region Public Methods
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
