// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SkillTreeSystem : ModuleRules
{
	public SkillTreeSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "Slate", "SlateCore" });

	}
}
