using System.IO;
using UnrealBuildTool;

public class BeamSDK : ModuleRules
{
	public BeamSDK(ReadOnlyTargetRules Target) : base(Target)
	{
		//PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		PCHUsage = PCHUsageMode.NoPCHs;

		PublicIncludePaths.AddRange(
			new string[]
			{
				Path.Combine(ModuleDirectory, "Public", "Models"),
				Path.Combine(ModuleDirectory, "Public", "Storage"),
				Path.Combine(ModuleDirectory, "Public", "Utils"),

				// Include the PlayerClient Public headers
				Path.Combine(PluginDirectory, "Source", "PlayerClient", "Public"),

				// Include the Openfort Public headers
				Path.Combine(PluginDirectory, "..", "Openfort", "Source", "Openfort", "Public"),
				Path.Combine(PluginDirectory, "..", "Openfort", "Source", "Openfort", "External"),
			}
		);
				
		
		PrivateIncludePaths.AddRange(
			new string[]
			{
				Path.Combine(ModuleDirectory, "Private", "Models"),
				Path.Combine(ModuleDirectory, "Private", "Storage"),
				Path.Combine(ModuleDirectory, "Private", "Utils"),
			}
		);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"HTTP",
				"Json",
				"JsonUtilities",
				"Serialization",
			}
		);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"PlayerClient",
				"Openfort",
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