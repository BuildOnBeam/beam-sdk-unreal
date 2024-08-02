/**
 * Player API
 * The Player API is a service to integrate your game with Beam
 *
 * OpenAPI spec version: 1.0.0
 * 
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * https://github.com/OpenAPITools/openapi-generator
 * Do not edit the class manually.
 */

#include "PlayerClientGetAssetsForUserBodyInput.h"

#include "PlayerClientModule.h"
#include "PlayerClientHelpers.h"

#include "Templates/SharedPointer.h"

namespace OpenAPI
{

inline FString ToString(const PlayerClientGetAssetsForUserBodyInput::SortDirectionEnum& Value)
{
	switch (Value)
	{
	case PlayerClientGetAssetsForUserBodyInput::SortDirectionEnum::Asc:
		return TEXT("asc");
	case PlayerClientGetAssetsForUserBodyInput::SortDirectionEnum::Desc:
		return TEXT("desc");
	}

	UE_LOG(LogPlayerClient, Error, TEXT("Invalid PlayerClientGetAssetsForUserBodyInput::SortDirectionEnum Value (%d)"), (int)Value);
	return TEXT("");
}

FString PlayerClientGetAssetsForUserBodyInput::EnumToString(const PlayerClientGetAssetsForUserBodyInput::SortDirectionEnum& EnumValue)
{
	return ToString(EnumValue);
}

inline bool FromString(const FString& EnumAsString, PlayerClientGetAssetsForUserBodyInput::SortDirectionEnum& Value)
{
	static TMap<FString, PlayerClientGetAssetsForUserBodyInput::SortDirectionEnum> StringToEnum = { 
		{ TEXT("asc"), PlayerClientGetAssetsForUserBodyInput::SortDirectionEnum::Asc },
		{ TEXT("desc"), PlayerClientGetAssetsForUserBodyInput::SortDirectionEnum::Desc }, };

	const auto Found = StringToEnum.Find(EnumAsString);
	if(Found)
		Value = *Found;

	return Found != nullptr;
}

bool PlayerClientGetAssetsForUserBodyInput::EnumFromString(const FString& EnumAsString, PlayerClientGetAssetsForUserBodyInput::SortDirectionEnum& EnumValue)
{
	return FromString(EnumAsString, EnumValue);
}

inline void WriteJsonValue(JsonWriter& Writer, const PlayerClientGetAssetsForUserBodyInput::SortDirectionEnum& Value)
{
	WriteJsonValue(Writer, ToString(Value));
}

inline bool TryGetJsonValue(const TSharedPtr<FJsonValue>& JsonValue, PlayerClientGetAssetsForUserBodyInput::SortDirectionEnum& Value)
{
	FString TmpValue;
	if (JsonValue->TryGetString(TmpValue))
	{
		if(FromString(TmpValue, Value))
			return true;
	}
	return false;
}

inline FString ToString(const PlayerClientGetAssetsForUserBodyInput::SortByEnum& Value)
{
	switch (Value)
	{
	case PlayerClientGetAssetsForUserBodyInput::SortByEnum::AcquiredAt:
		return TEXT("acquiredAt");
	case PlayerClientGetAssetsForUserBodyInput::SortByEnum::LastAppraisalValue:
		return TEXT("lastAppraisalValue");
	}

	UE_LOG(LogPlayerClient, Error, TEXT("Invalid PlayerClientGetAssetsForUserBodyInput::SortByEnum Value (%d)"), (int)Value);
	return TEXT("");
}

FString PlayerClientGetAssetsForUserBodyInput::EnumToString(const PlayerClientGetAssetsForUserBodyInput::SortByEnum& EnumValue)
{
	return ToString(EnumValue);
}

inline bool FromString(const FString& EnumAsString, PlayerClientGetAssetsForUserBodyInput::SortByEnum& Value)
{
	static TMap<FString, PlayerClientGetAssetsForUserBodyInput::SortByEnum> StringToEnum = { 
		{ TEXT("acquiredAt"), PlayerClientGetAssetsForUserBodyInput::SortByEnum::AcquiredAt },
		{ TEXT("lastAppraisalValue"), PlayerClientGetAssetsForUserBodyInput::SortByEnum::LastAppraisalValue }, };

	const auto Found = StringToEnum.Find(EnumAsString);
	if(Found)
		Value = *Found;

	return Found != nullptr;
}

bool PlayerClientGetAssetsForUserBodyInput::EnumFromString(const FString& EnumAsString, PlayerClientGetAssetsForUserBodyInput::SortByEnum& EnumValue)
{
	return FromString(EnumAsString, EnumValue);
}

inline void WriteJsonValue(JsonWriter& Writer, const PlayerClientGetAssetsForUserBodyInput::SortByEnum& Value)
{
	WriteJsonValue(Writer, ToString(Value));
}

inline bool TryGetJsonValue(const TSharedPtr<FJsonValue>& JsonValue, PlayerClientGetAssetsForUserBodyInput::SortByEnum& Value)
{
	FString TmpValue;
	if (JsonValue->TryGetString(TmpValue))
	{
		if(FromString(TmpValue, Value))
			return true;
	}
	return false;
}

void PlayerClientGetAssetsForUserBodyInput::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	if (SortDirection.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("sortDirection")); WriteJsonValue(Writer, SortDirection.GetValue());
	}
	if (SortBy.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("sortBy")); WriteJsonValue(Writer, SortBy.GetValue());
	}
	if (Contract.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("contract")); WriteJsonValue(Writer, Contract.GetValue());
	}
	if (IncludeAttributes.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("includeAttributes")); WriteJsonValue(Writer, IncludeAttributes.GetValue());
	}
	if (Continuation.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("continuation")); WriteJsonValue(Writer, Continuation.GetValue());
	}
	if (ChainId.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("chainId")); WriteJsonValue(Writer, ChainId.GetValue());
	}
	if (Limit.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("limit")); WriteJsonValue(Writer, Limit.GetValue());
	}
	Writer->WriteObjectEnd();
}

bool PlayerClientGetAssetsForUserBodyInput::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("sortDirection"), SortDirection);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("sortBy"), SortBy);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("contract"), Contract);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("includeAttributes"), IncludeAttributes);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("continuation"), Continuation);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("chainId"), ChainId);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("limit"), Limit);

	return ParseSuccess;
}

}