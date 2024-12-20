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

#include "PlayerClientCreateTransactionRequestInput.h"

#include "PlayerClientModule.h"
#include "PlayerClientHelpers.h"

#include "Templates/SharedPointer.h"

namespace OpenAPI
{

inline FString ToString(const PlayerClientCreateTransactionRequestInput::OperationProcessingEnum& Value)
{
	switch (Value)
	{
	case PlayerClientCreateTransactionRequestInput::OperationProcessingEnum::SignOnly:
		return TEXT("SignOnly");
	case PlayerClientCreateTransactionRequestInput::OperationProcessingEnum::Execute:
		return TEXT("Execute");
	}

	UE_LOG(LogPlayerClient, Error, TEXT("Invalid PlayerClientCreateTransactionRequestInput::OperationProcessingEnum Value (%d)"), (int)Value);
	return TEXT("");
}

FString PlayerClientCreateTransactionRequestInput::EnumToString(const PlayerClientCreateTransactionRequestInput::OperationProcessingEnum& EnumValue)
{
	return ToString(EnumValue);
}

inline bool FromString(const FString& EnumAsString, PlayerClientCreateTransactionRequestInput::OperationProcessingEnum& Value)
{
	static TMap<FString, PlayerClientCreateTransactionRequestInput::OperationProcessingEnum> StringToEnum = { 
		{ TEXT("SignOnly"), PlayerClientCreateTransactionRequestInput::OperationProcessingEnum::SignOnly },
		{ TEXT("Execute"), PlayerClientCreateTransactionRequestInput::OperationProcessingEnum::Execute }, };

	const auto Found = StringToEnum.Find(EnumAsString);
	if(Found)
		Value = *Found;

	return Found != nullptr;
}

bool PlayerClientCreateTransactionRequestInput::EnumFromString(const FString& EnumAsString, PlayerClientCreateTransactionRequestInput::OperationProcessingEnum& EnumValue)
{
	return FromString(EnumAsString, EnumValue);
}

inline void WriteJsonValue(JsonWriter& Writer, const PlayerClientCreateTransactionRequestInput::OperationProcessingEnum& Value)
{
	WriteJsonValue(Writer, ToString(Value));
}

inline bool TryGetJsonValue(const TSharedPtr<FJsonValue>& JsonValue, PlayerClientCreateTransactionRequestInput::OperationProcessingEnum& Value)
{
	FString TmpValue;
	if (JsonValue->TryGetString(TmpValue))
	{
		if(FromString(TmpValue, Value))
			return true;
	}
	return false;
}

void PlayerClientCreateTransactionRequestInput::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	Writer->WriteIdentifierPrefix(TEXT("interactions")); WriteJsonValue(Writer, Interactions);
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
	if (ChainId.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("chainId")); WriteJsonValue(Writer, ChainId.GetValue());
	}
	if (OperationProcessing.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("operationProcessing")); WriteJsonValue(Writer, OperationProcessing.GetValue());
	}
	Writer->WriteObjectEnd();
}

bool PlayerClientCreateTransactionRequestInput::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("interactions"), Interactions);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("optimistic"), Optimistic);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("sponsor"), Sponsor);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("policyId"), PolicyId);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("chainId"), ChainId);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("operationProcessing"), OperationProcessing);

	return ParseSuccess;
}

}
