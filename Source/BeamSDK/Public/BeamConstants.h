#include "CoreMinimal.h"
#include "Containers/UnrealString.h"


struct FBeamConstants
{
	static const int DefaultChainId = 13337;

	static const FString BeamAPIKeyHeader;

	struct Storage
	{
		static const FString BeamSigningKey;
		static const FString BeamSession;
	};
};
