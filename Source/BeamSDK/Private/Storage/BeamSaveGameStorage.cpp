#include "BeamSaveGameStorage.h"

#if PLATFORM_WINDOWS
// Clear the Microsoft GetObject Macro so it doesn't cause annoying build errors regarding GetObjectW.
#include "Microsoft/WindowsHWrapper.h"
#endif

#include "Kismet/GameplayStatics.h"

UBeamSaveGameStorage* UBeamSaveGameStorage::LoadOrCreate(const FString& BeamStorageSlotName)
{
	UBeamSaveGameStorage* BeamStorage = Cast<UBeamSaveGameStorage>(UGameplayStatics::LoadGameFromSlot(BeamStorageSlotName, 0));
	if (!BeamStorage)
	{
		BeamStorage = Cast<UBeamSaveGameStorage>(UGameplayStatics::CreateSaveGameObject(StaticClass()));
		BeamStorage->bIsDirty = true;
		BeamStorage->beamStorageSlotName = BeamStorageSlotName;
	} else
	{
		BeamStorage->beamStorageSlotName = BeamStorageSlotName;
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
		UGameplayStatics::SaveGameToSlot(this, beamStorageSlotName, 0);
	}
}
