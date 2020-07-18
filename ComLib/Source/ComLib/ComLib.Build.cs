// Some copyright should be here...

using UnrealBuildTool;

public class ComLib : ModuleRules
{
    public ComLib(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicIncludePaths.AddRange(
             new string[] {
                 // ... add public include paths required here ...
             }
             );
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core"
				// ... add other public dependencies that you statically link with here ...
			}
            );
        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "UMG",
                "InputCore",
                "CoreUObject",
                "Engine",
                "HeadMountedDisplay",
                "Slate",
                "SlateCore",
                "Json",
                "JsonUtilities",
                "ApplicationCore",
				// ... add private dependencies that you statically link with here ...	
			}
            );
        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
				// ... add any modules that your module loads dynamically here ...
			}
            );
    }

}
