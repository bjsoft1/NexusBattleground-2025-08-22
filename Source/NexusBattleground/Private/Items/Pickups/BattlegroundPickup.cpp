// Fill out your copyright notice in the Description page of Project Settings.

#pragma region Default System Header Files
#include "BattlegroundPickup.h"
#include "UObject/UObjectGlobals.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"
#pragma endregion Default System Header Files


#pragma region NexusBattleground Header Files
#include "BattlegroundPickupManager.h"
#pragma endregion NexusBattleground Header Files




#pragma region Constructors and Overrides
ABattlegroundPickup::ABattlegroundPickup(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
    AActor::SetReplicates(true);
    AActor::SetReplicateMovement(true);
    AActor::PrimaryActorTick.bCanEverTick = false;
    AActor::RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}
void ABattlegroundPickup::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ABattlegroundPickup, DatatableRowId);
    DOREPLIFETIME(ABattlegroundPickup, PickupAmount);
}
#pragma endregion Constructors and Overrides


#pragma region Lifecycle Overrides
void ABattlegroundPickup::BeginPlay()
{
    if (AActor::HasAuthority())
    {
        FVector traceStart = GetActorLocation();
        FVector traceEnd = traceStart + FVector(0.0f, 0.0f, -1000.0f);
        TArray<AActor*> actorsToIgnore;
        actorsToIgnore.Add(this);
        TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
        objectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
        FHitResult hitResult;
        bool isHit = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), traceStart, traceEnd, objectTypes, false, actorsToIgnore, EDrawDebugTrace::None, hitResult, true);
        if (isHit) AActor::SetActorLocation(hitResult.ImpactPoint);
    }
}
void ABattlegroundPickup::EndPlay(const EEndPlayReason::Type endPlayReason)
{
    Super::EndPlay(endPlayReason);

    if (this->PickupMesh)
    {
        this->PickupMesh->DestroyComponent(false);
        this->PickupMesh = nullptr;
    }
}
#pragma endregion Lifecycle Overrides


#pragma region Public Methods
void ABattlegroundPickup::InitializePickup(const FName& rowId, uint16 amount)
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
void ABattlegroundPickup::SetHighlight(bool isHighlight)
{
    if (this->PickupMesh == nullptr) return;

    this->PickupMesh->SetRenderCustomDepth(isHighlight);
    this->PickupMesh->SetCustomDepthStencilValue(isHighlight ? 1 : 0);
}
#pragma endregion Public Methods


#pragma region Protected Methods
#pragma endregion Protected Methods


#pragma region Private Helper Methods
#pragma endregion Private Helper Methods


#pragma region Input Bindings
#pragma endregion Input Bindings

#pragma region Callbacks
#pragma endregion Callbacks


#pragma region Server/Multicast RPC
#pragma endregion Server/Multicast RPC


#pragma region Client/OnRep RPC
void ABattlegroundPickup::OnRep_DatatableRowId()
{

    if (this->PickupData.StaticMesh.IsValid() || this->DatatableRowId.IsNone()) return;

    ABattlegroundPickupManager* pickupManager = ABattlegroundPickupManager::GetManager(GetWorld());
    if (!pickupManager) return;

    this->PickupMesh = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(), TEXT("DynamicPickupMesh"));
    this->PickupMesh->RegisterComponent();
    this->PickupMesh->AttachToComponent(AActor::RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

    this->PickupMesh->SetSimulatePhysics(false);
    this->PickupMesh->SetEnableGravity(false);

    PickupMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    this->PickupMesh->SetCollisionObjectType(ECC_WorldDynamic); // Or custom channel
    this->PickupMesh->SetCollisionResponseToAllChannels(ECR_Ignore); // Ignore everything by default
    this->PickupMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore); // Ignore pawns
    this->PickupMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block); // Still traceable

    this->PickupData = pickupManager->GetPickupData(this->DatatableRowId);
    if (!this->PickupData.StaticMesh.IsNull())
    {
		EPickupTypes pickupType;
		uint8 pickupSubType;

        // TODO: Handle failure
        if (BattlegroundUtilities::ParsePickupRowName(this->DatatableRowId, pickupType, pickupSubType))
        {
			this->PickupData.PickupType = pickupType;
			this->PickupData.Subtype = pickupSubType;
        }
        else NEXUS_ERROR("Failed to parse pickup row name: %s", *this->DatatableRowId.ToString());


        UStaticMesh* staticMesh = this->PickupData.StaticMesh.LoadSynchronous();
        if (staticMesh)
        {
            this->PickupMesh->SetStaticMesh(staticMesh);
            this->PickupMesh->SetWorldScale3D(FVector(this->PickupData.DefaultScale));
        }
    }
}
#pragma endregion Client/OnRep RPC


#pragma region Debug Methods
#pragma endregion Debug Methods

