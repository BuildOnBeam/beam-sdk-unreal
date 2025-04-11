#include "BeamSaveGameStorage.h"

#if PLATFORM_WINDOWS
// Clear the Microsoft GetObject Macro so it doesn't cause annoying build errors regarding GetObjectW.
#include "Microsoft/WindowsHWrapper.h"
#endif

#include "Kismet/GameplayStatics.h"

#define DEFAULT_SLOT_NAME	TEXT("BeamStorage")
namespace
{
	FString BeamStorageSlotName(DEFAULT_SLOT_NAME);
}

UBeamSaveGameStorage* UBeamSaveGameStorage::LoadOrCreate(const FString& CustomSlot)
{
	BeamStorageSlotName = DEFAULT_SLOT_NAME;
	BeamStorageSlotName += CustomSlot;

	UBeamSaveGameStorage* BeamStorage = Cast<UBeamSaveGameStorage>(UGameplayStatics::LoadGameFromSlot(BeamStorageSlotName, 0));
	if (!BeamStorage)
	{
		BeamStorage = Cast<UBeamSaveGameStorage>(UGameplayStatics::CreateSaveGameObject(StaticClass()));
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
