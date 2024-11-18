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

#include "PlayerClientCancelAssetListingRequestInput.h"

#include "PlayerClientModule.h"
#include "PlayerClientHelpers.h"

#include "Templates/SharedPointer.h"

namespace OpenAPI
{

inline FString ToString(const PlayerClientCancelAssetListingRequestInput::OperationProcessingEnum& Value)
{
	switch (Value)
	{
	case PlayerClientCancelAssetListingRequestInput::OperationProcessingEnum::SignOnly:
		return TEXT("SignOnly");
	case PlayerClientCancelAssetListingRequestInput::OperationProcessingEnum::Execute:
		return TEXT("Execute");
	}

	UE_LOG(LogPlayerClient, Error, TEXT("Invalid PlayerClientCancelAssetListingRequestInput::OperationProcessingEnum Value (%d)"), (int)Value);
	return TEXT("");
}

FString PlayerClientCancelAssetListingRequestInput::EnumToString(const PlayerClientCancelAssetListingRequestInput::OperationProcessingEnum& EnumValue)
{
	return ToString(EnumValue);
}

inline bool FromString(const FString& EnumAsString, PlayerClientCancelAssetListingRequestInput::OperationProcessingEnum& Value)
{
	static TMap<FString, PlayerClientCancelAssetListingRequestInput::OperationProcessingEnum> StringToEnum = { 
		{ TEXT("SignOnly"), PlayerClientCancelAssetListingRequestInput::OperationProcessingEnum::SignOnly },
		{ TEXT("Execute"), PlayerClientCancelAssetListingRequestInput::OperationProcessingEnum::Execute }, };

	const auto Found = StringToEnum.Find(EnumAsString);
	if(Found)
		Value = *Found;

	return Found != nullptr;
}

bool PlayerClientCancelAssetListingRequestInput::EnumFromString(const FString& EnumAsString, PlayerClientCancelAssetListingRequestInput::OperationProcessingEnum& EnumValue)
{
	return FromString(EnumAsString, EnumValue);
}

inline void WriteJsonValue(JsonWriter& Writer, const PlayerClientCancelAssetListingRequestInput::OperationProcessingEnum& Value)
{
	WriteJsonValue(Writer, ToString(Value));
}

inline bool TryGetJsonValue(const TSharedPtr<FJsonValue>& JsonValue, PlayerClientCancelAssetListingRequestInput::OperationProcessingEnum& Value)
{
	FString TmpValue;
	if (JsonValue->TryGetString(TmpValue))
	{
		if(FromString(TmpValue, Value))
			return true;
	}
	return false;
}

void PlayerClientCancelAssetListingRequestInput::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	if (Optimistic.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("optimistic")); WriteJsonValue(Writer, Optimistic.GetValue());
	}
	if (Sponsor.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("sponsor")); WriteJsonValue(Writer, Sponsor.GetValue());
	}
	if (PolicyId.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("policyId")); WriteJsonValue(Writer, PolicyId.GetValue());
	}
	if (OperationProcessing.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("operationProcessing")); WriteJsonValue(Writer, OperationProcessing.GetValue());
	}
	Writer->WriteObjectEnd();
}

bool PlayerClientCancelAssetListingRequestInput::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("optimistic"), Optimistic);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("sponsor"), Sponsor);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("policyId"), PolicyId);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("operationProcessing"), OperationProcessing);

	return ParseSuccess;
}

}
