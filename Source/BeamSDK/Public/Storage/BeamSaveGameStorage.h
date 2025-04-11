#pragma once

#include "GameFramework/SaveGame.h"
#include "BeamStorageInterface.h"

#include "BeamSaveGameStorage.generated.h"

// This class does not need to be modified.
UCLASS()
class BEAMSDK_API UBeamSaveGameStorage : public USaveGame, public IBeamStorageInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Beam Storage")
	TMap<FString, FString> BeamStorageRegistry;

	static UBeamSaveGameStorage* LoadOrCreate(const FString& CustomSlot = "");

	virtual FString Get(FString Key) const override;

	virtual void Set(FString Key, FString Value) override;

	virtual void Delete(FString Key) override;

	virtual void Save() override;

protected:
	bool bIsDirty = false;
};
