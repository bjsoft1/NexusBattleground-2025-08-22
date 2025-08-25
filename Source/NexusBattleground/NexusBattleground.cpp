// Copyright Epic Games, Inc. All Rights Reserved.

#include "NexusBattleground.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Modules/ModuleManager.h"
#include "Styling/SlateStyleRegistry.h"
#include "NexusBattlegroundDelegates.h"

#include "BattlegroundStyles.h"

void FNexusBattlegroundGameModule::StartupModule()
{
	// We do not need to call Super::StartupModule() because FDefaultGameModuleImpl::StartupModule is empty.

	InitializeBattlegroundDelegates();

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));

	//Hot reload hack
	FSlateStyleRegistry::UnRegisterSlateStyle(WidgetKeys::WIDGET_STYLE_KEY);
	FBattlegroundStyles::Initialize();
}

void FNexusBattlegroundGameModule::ShutdownModule()
{
	// We do not need to call Super::ShutdownModule() because FDefaultGameModuleImpl::ShutdownModule is empty.

	FBattlegroundStyles::Shutdown();
}

IMPLEMENT_PRIMARY_GAME_MODULE(FNexusBattlegroundGameModule, NexusBattleground, "NexusBattleground");