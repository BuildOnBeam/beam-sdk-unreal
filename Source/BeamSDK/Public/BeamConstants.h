#pragma once

#include "CoreMinimal.h"
#include "Containers/UnrealString.h"


struct FBeamConstants
{
	static const int DefaultChainId = 13337;

	static const FString BeamAPIKeyHeader;
	static const FString BeamSDKHeader;
	static const FString BeamSDKUnreal;

	struct Storage
	{
		static const FString BeamSigningKey;
		static const FString BeamSession;
	};
};
