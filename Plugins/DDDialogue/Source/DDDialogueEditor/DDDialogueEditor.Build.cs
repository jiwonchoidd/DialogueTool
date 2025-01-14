using UnrealBuildTool;

public class DDDialogueEditor : ModuleRules
{
    public DDDialogueEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "UnrealEd", // UFactory와 관련된 주요 모듈
                "GraphEditor",
                "PropertyEditor",
                "Kismet",
                "InputCore",
                "ApplicationCore", 
                "DDDialogue",
            }
        );
    }
}