#include "BeamUtils.h"

DEFINE_LOG_CATEGORY(LogBeamUtils);

bool FBeamUtils::DeserializeJson(const FString& InJsonString, TSharedPtr<FJsonObject>& OutJsonObject)
{
	bool bIsDeseriliazeSuccessful = false;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(InJsonString);
	bIsDeseriliazeSuccessful = FJsonSerializer::Deserialize(JsonReader, OutJsonObject);
	return bIsDeseriliazeSuccessful;
}

