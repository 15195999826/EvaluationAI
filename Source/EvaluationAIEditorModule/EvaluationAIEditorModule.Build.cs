using UnrealBuildTool;

public class EvaluationAIEditorModule : ModuleRules
{
    public EvaluationAIEditorModule(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "EvaluationAI",
                "UnrealEd",
                "PropertyEditor",
                "DetailCustomizations",
                "ToolMenus",
                "EditorStyle",
                "EditorWidgets",
                "Slate",
                "SlateCore",
                "GameplayTags"
            }
        );
		
        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "EditorSubsystem",
                "TargetPlatform"
            }
        );
    }
}