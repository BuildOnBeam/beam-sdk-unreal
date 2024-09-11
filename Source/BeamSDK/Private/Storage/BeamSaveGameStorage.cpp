#include "BeamSaveGameStorage.h"

#if PLATFORM_WINDOWS
	...
// Clear the Microsoft GetObject Macro so it doesn't cause annoying build errors regarding GetObjectW.
#include "Microsoft/PreWindowsApi.h"
#include "Microsoft/PostWindowsApi.h"
#endif

#include "Kismet/GameplayStatics.h"

namespace
{
	static const FString BeamStorageSlotName(TEXT("BeamStorage"));
}

UBeamSaveGameStorage* UBeamSaveGameStorage::LoadOrCreate()
{
	UBeamSaveGameStorage* BeamStorage = Cast<UBeamSaveGameStorage>(UGameplayStatics::LoadGameFromSlot(BeamStorageSlotName, 0));
	if (!BeamStorage)
	{
		BeamStorage = Cast<UBeamSaveGameStorage>(UGameplayStatics::CreateSaveGameObject(UBeamSaveGameStorage::StaticClass()));
		BeamStorage->bIsDirty = true;
	}
	return BeamStorage;
}

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
	if (BeamStorageRegistry.Contains(Key))
	{
		BeamStorageRegistry[Key] = Value;
	}
	else
	{
		BeamStorageRegistry.Add(Key, Value);
	}
	bIsDirty = true;
}

void UBeamSaveGameStorage::Delete(FString Key)
{
	if (BeamStorageRegistry.Contains(Key))
	{
		BeamStorageRegistry.Remove(Key);
		bIsDirty = true;
	}
}

void UBeamSaveGameStorage::Save()
{
	// Write save file to disk
	if (bIsDirty)
	{
		UGameplayStatics::SaveGameToSlot(this, BeamStorageSlotName, 0);
	}
}
