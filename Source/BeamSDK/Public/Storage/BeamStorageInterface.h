#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "BeamStorageInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBeamStorageInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BEAMSDK_API IBeamStorageInterface
{
	GENERATED_BODY()

public:

	virtual FString Get(FString Key) const PURE_VIRTUAL(IBeamStorageInterface::Get, return TEXT(""); );

	virtual void Set(FString Key, FString Value) PURE_VIRTUAL(IBeamStorageInterface::Set, return; );

	virtual void Delete(FString Key) PURE_VIRTUAL(IBeamStorageInterface::Delete, return; );

	virtual void Save() PURE_VIRTUAL(IBeamStorageInterface::Save, return; );
};
