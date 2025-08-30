// Copyright Epic Games, Inc. All Rights Reserved.
// NOTE: This file's all code logic comes from Unreal Engine samples (ShooterGame). And it is modified to fit our game.

#include "NexusBattlegroundDelegates.h"
#include "NexusBattleground.h"
#include "BattlegroundGameState.h"
#include "BattlegroundPlayerState.h"
#include "IPlatformFilePak.h"
#include "UObject/PackageReload.h"
#include "Engine/GameEngine.h"
#include "GameDelegates.h"

#include "BattlegroundUtilities.h"

// Global struct for registering delegates super early
struct FBattlegroundGlobalDelegateInit
{
	FBattlegroundGlobalDelegateInit()
	{
		FPakPlatformFile::FPakSigningFailureHandlerData& handlerData = FPakPlatformFile::GetPakSigningFailureHandlerData();
		{
			FScopeLock Lock(&handlerData.Lock);
			handlerData.ChunkSignatureCheckFailedDelegate.AddStatic(FBattlegroundGlobalDelegateInit::HandlePakChunkSignatureCheckFailed);
			handlerData.MasterSignatureTableCheckFailedDelegate.AddStatic(FBattlegroundGlobalDelegateInit::HandlePakMasterSignatureTableCheckFailure);
		}

		FPakPlatformFile::GetPakSetIndexSettingsDelegate().BindStatic(GetPakSetIndexSettings);
	}

	static void HandlePakChunkSignatureCheckFailed(const FPakChunkSignatureCheckFailedData& data)
	{

		NEXUS_ERROR("Pak chunk signature check failed!");
	}

	static void HandlePakMasterSignatureTableCheckFailure(const FString& inPakFilename)
	{
		NEXUS_ERROR("Pak master signature table check failed for pak '%s'", *inPakFilename);
	}

	static void GetPakSetIndexSettings(bool& isKeepFullDirectory, bool& isValidatePruning, bool& isDelayPruning)
	{
		// Keep the full directory of filenames in PakFileIndexes, so that FindOrLoadAssetsByPath will be able to find files in a given path
		isKeepFullDirectory = true;
	}
}
GBattlegroundGlobalDelegateInit;

// respond to requests from a companion app
static void WebServerDelegate(int32 UserIndex, const FString& Action, const FString& URL, const TMap<FString, FString>& Params, TMap<FString, FString>& Response)
{
	// TODO: implement web server actions
}

static void ExtendedSaveGameInfoDelegate(const TCHAR* SaveName, const EGameDelegates_SaveGame Key, FString& Value)
{
	static const int32 MAX_SAVEGAME_SIZE = 100 * 1024;
	switch(Key)
	{
		case EGameDelegates_SaveGame::MaxSize:			
			Value = FString::Printf(TEXT("%i"), MAX_SAVEGAME_SIZE);
			break;
		case EGameDelegates_SaveGame::Title:
			Value = TEXT("Battleground");
			break;
		case EGameDelegates_SaveGame::SubTitle:
			Value = TEXT("The Shootening");
			break;
		case EGameDelegates_SaveGame::Detail:
			Value = TEXT("Battleground User Settings");
			break;
		default:
			break;
	}
}

static void ReloadHandler( EPackageReloadPhase ReloadPhase, FPackageReloadedEvent* Event)
{
	if ( ReloadPhase == EPackageReloadPhase::PostPackageFixup)
	{
		
	}
}

#define EXPERIMENTAL_ENABLEHOTRELOAD 0
static void ReloadPackagesCallback( const TArray<FString>& packageNames)
{
#if EXPERIMENTAL_ENABLEHOTRELOAD
	TArray<UPackage*> packagesToReload;
	TArray<UPackage*> materialPackagesToReload;
	for (const FString&packageName : packageNames)
	{
		UPackage* package = FindPackage(nullptr, *packageName);

		if (package == nullptr)
		{
			NEXUS_ERROR("Unable to find package in memory %s", *packageName);
		}
		else
		{
			if ( package->HasAnyPackageFlags(PKG_ContainsMap || PKG_ContainsMap) ) continue;
			packagesToReload.Add(package);
		}
	}


	// see what's in these packages

	if (packagesToReload.Num())
	{
		SortPackagesForReload(packagesToReload);

		TArray<FReloadPackageData> PackagesToReloadData;
		PackagesToReloadData.Empty(packagesToReload.Num());
		for (UPackage* packageToReload : packagesToReload)
		{
			PackagesToReloadData.Emplace(packageToReload, LOAD_None);
		}

		TArray<UPackage*> reloadedPackages;

		FDelegateHandle delegateHandle = FCoreUObjectDelegates::OnPackageReloaded.AddStatic(&ReloadHandler);

		FText errorMessage;
		GShouldVerifyGCAssumptions = false;
		GUObjectArray.DisableDisregardForGC();

		::ReloadPackages(PackagesToReloadData, reloadedPackages, 500);

		FCoreUObjectDelegates::OnPackageReloaded.Remove(delegateHandle);
	}
#endif
}

void InitializeBattlegroundDelegates()
{
	FGameDelegates::Get().GetWebServerActionDelegate() = FWebServerActionDelegate::CreateStatic(WebServerDelegate);
	FGameDelegates::Get().GetExtendedSaveGameInfoDelegate() = FExtendedSaveGameInfoDelegate::CreateStatic(ExtendedSaveGameInfoDelegate);

	FCoreUObjectDelegates::NetworkFileRequestPackageReload.BindStatic(&ReloadPackagesCallback);
}
