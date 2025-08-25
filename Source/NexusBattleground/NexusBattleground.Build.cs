// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NexusBattleground : ModuleRules
{
    public NexusBattleground(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "AIModule",
            "StateTreeModule",
            "GameplayStateTreeModule",
            "UMG",
            "Slate",
            "SlateCore",
        });

        PrivateDependencyModuleNames.AddRange(new string[] {
        });

        PublicIncludePaths.AddRange(new string[] {
            "NexusBattleground",

            // ------- Public Include Paths -------
            "NexusBattleground/Public",
            "NexusBattleground/Public/Characters",
            "NexusBattleground/Public/Core",
            "NexusBattleground/Public/Gameplay",
            "NexusBattleground/Public/Gameplay/Controllers",
            "NexusBattleground/Public/Gameplay/GameModes",
            "NexusBattleground/Public/Gameplay/HUD",
            "NexusBattleground/Public/Gameplay/States",
            "NexusBattleground/Public/Items",
            "NexusBattleground/Public/Items/Pickups",
            "NexusBattleground/Public/Items/Weapons",
            "NexusBattleground/Public/Items/Menu",
            "NexusBattleground/Public/Menu/Widgets",

            //------- Privates Include Paths -------
            "NexusBattleground/Private",
            "NexusBattleground/Private/Utilities",

        });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
