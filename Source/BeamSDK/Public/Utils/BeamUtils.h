#pragma once

#include "JsonObjectConverter.h"

class FProperty;
class UStruct;
class FJsonObject;

DECLARE_LOG_CATEGORY_EXTERN(LogBeamUtils, Log, All);

class FBeamUtils
{
public:

	template<typename TStructType>
	static bool JsonToStruct(const FString& InJsonString, TStructType& OutStruct)
	{
		if (!FJsonObjectConverter::JsonObjectStringToUStruct(InJsonString, &OutStruct))
		{
			UE_LOG(LogBeamUtils, Error, TEXT("JsonToStruct failed. struct=[%s], json=[%s]"), *TStructType::StaticStruct()->GetName(), *InJsonString);
			return false;
		}
		return true;
	}

	static bool DeserializeJson(const FString& InJsonString, TSharedPtr<FJsonObject>& OutJsonObject);
};
