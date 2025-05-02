#pragma once

#include "BeamEnvironment.generated.h"

UENUM()
enum class EBeamEnvironment : uint8
{
	Mainnet UMETA(DisplayName = "Mainnet", Deprecated = "Use Production that supports both Mainnet and Testnet chains"),
	Testnet UMETA(DisplayName = "Testnet", Deprecated = "Now named Beta, supports only Testnet chains"),
	Beta UMETA(DisplayName = "Beta"),
	Production UMETA(DisplayName = "Production")
};