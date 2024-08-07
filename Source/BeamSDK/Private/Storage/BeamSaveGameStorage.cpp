#include "BeamSaveGameStorage.h"

FString UBeamSaveGameStorage::Get(FString Key) const
{
	if (!BeamStorageRegistry.Contains(Key))
	{
		// TODO: Log Key Not Found
		return TEXT("");
	}
	return BeamStorageRegistry[Key];
}

void UBeamSaveGameStorage::Set(FString Key, FString Value)
{
	BeamStorageRegistry[Key] = Value;
}

void UBeamSaveGameStorage::Delete(FString Key)
{
	BeamStorageRegistry.Remove(Key);
}

