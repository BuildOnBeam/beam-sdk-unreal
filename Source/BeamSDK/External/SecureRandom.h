#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSecureRandom, Log, All);

void GenerateSecureRandomBytes(uint8* Buffer, size_t Length);