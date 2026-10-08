// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class OpenWorldMap : ModuleRules
{
	public OpenWorldMap(ReadOnlyTargetRules Target) : base(Target)
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
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"OpenWorldMap",
			"OpenWorldMap/Variant_Platforming",
			"OpenWorldMap/Variant_Platforming/Animation",
			"OpenWorldMap/Variant_Combat",
			"OpenWorldMap/Variant_Combat/AI",
			"OpenWorldMap/Variant_Combat/Animation",
			"OpenWorldMap/Variant_Combat/Gameplay",
			"OpenWorldMap/Variant_Combat/Interfaces",
			"OpenWorldMap/Variant_Combat/UI",
			"OpenWorldMap/Variant_SideScrolling",
			"OpenWorldMap/Variant_SideScrolling/AI",
			"OpenWorldMap/Variant_SideScrolling/Gameplay",
			"OpenWorldMap/Variant_SideScrolling/Interfaces",
			"OpenWorldMap/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
