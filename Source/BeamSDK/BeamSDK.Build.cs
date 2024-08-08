using System.IO;
using UnrealBuildTool;

public class BeamSDK : ModuleRules
{
	public BeamSDK(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.NoPCHs;

		PublicIncludePaths.AddRange(
			new string[]
			{
				Path.Combine(ModuleDirectory, "Public", "Models"),
				Path.Combine(ModuleDirectory, "Public", "Storage"),
				Path.Combine(ModuleDirectory, "Public", "Utils"),

				// Include Openfort support for KeyPair
				Path.Combine(ModuleDirectory, "External"),
				Path.Combine(ModuleDirectory, "External", "Openfort"),

				// Include the PlayerClient Public headers
				Path.Combine(PluginDirectory, "Source", "PlayerClient", "Public"),
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
			}
		);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
		);


		// Required for Openfort support for KeyPair
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "External/libsecp256k1.lib"));
		}
		if (Target.Platform == UnrealTargetPlatform.Linux || Target.Platform == UnrealTargetPlatform.Mac)
		{
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "External/libsecp256k1.a"));
		}
	}
}