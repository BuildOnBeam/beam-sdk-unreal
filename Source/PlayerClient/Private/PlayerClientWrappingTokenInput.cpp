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

#include "PlayerClientWrappingTokenInput.h"

#include "PlayerClientModule.h"
#include "PlayerClientHelpers.h"

#include "Templates/SharedPointer.h"

namespace OpenAPI
{

inline FString ToString(const PlayerClientWrappingTokenInput::OperationProcessingEnum& Value)
{
	switch (Value)
	{
	case PlayerClientWrappingTokenInput::OperationProcessingEnum::SignOnly:
		return TEXT("SignOnly");
	case PlayerClientWrappingTokenInput::OperationProcessingEnum::Execute:
		return TEXT("Execute");
	}

	UE_LOG(LogPlayerClient, Error, TEXT("Invalid PlayerClientWrappingTokenInput::OperationProcessingEnum Value (%d)"), (int)Value);
	return TEXT("");
}

FString PlayerClientWrappingTokenInput::EnumToString(const PlayerClientWrappingTokenInput::OperationProcessingEnum& EnumValue)
{
	return ToString(EnumValue);
}

inline bool FromString(const FString& EnumAsString, PlayerClientWrappingTokenInput::OperationProcessingEnum& Value)
{
	static TMap<FString, PlayerClientWrappingTokenInput::OperationProcessingEnum> StringToEnum = { 
		{ TEXT("SignOnly"), PlayerClientWrappingTokenInput::OperationProcessingEnum::SignOnly },
		{ TEXT("Execute"), PlayerClientWrappingTokenInput::OperationProcessingEnum::Execute }, };

	const auto Found = StringToEnum.Find(EnumAsString);
	if(Found)
		Value = *Found;

	return Found != nullptr;
}

bool PlayerClientWrappingTokenInput::EnumFromString(const FString& EnumAsString, PlayerClientWrappingTokenInput::OperationProcessingEnum& EnumValue)
{
	return FromString(EnumAsString, EnumValue);
}

inline void WriteJsonValue(JsonWriter& Writer, const PlayerClientWrappingTokenInput::OperationProcessingEnum& Value)
{
	WriteJsonValue(Writer, ToString(Value));
}

inline bool TryGetJsonValue(const TSharedPtr<FJsonValue>& JsonValue, PlayerClientWrappingTokenInput::OperationProcessingEnum& Value)
{
	FString TmpValue;
	if (JsonValue->TryGetString(TmpValue))
	{
		if(FromString(TmpValue, Value))
			return true;
	}
	return false;
}

inline FString ToString(const PlayerClientWrappingTokenInput::AuthProviderEnum& Value)
{
	switch (Value)
	{
	case PlayerClientWrappingTokenInput::AuthProviderEnum::Any:
		return TEXT("Any");
	case PlayerClientWrappingTokenInput::AuthProviderEnum::Google:
		return TEXT("Google");
	case PlayerClientWrappingTokenInput::AuthProviderEnum::Discord:
		return TEXT("Discord");
	case PlayerClientWrappingTokenInput::AuthProviderEnum::Apple:
		return TEXT("Apple");
	}

	UE_LOG(LogPlayerClient, Error, TEXT("Invalid PlayerClientWrappingTokenInput::AuthProviderEnum Value (%d)"), (int)Value);
	return TEXT("");
}

FString PlayerClientWrappingTokenInput::EnumToString(const PlayerClientWrappingTokenInput::AuthProviderEnum& EnumValue)
{
	return ToString(EnumValue);
}

inline bool FromString(const FString& EnumAsString, PlayerClientWrappingTokenInput::AuthProviderEnum& Value)
{
	static TMap<FString, PlayerClientWrappingTokenInput::AuthProviderEnum> StringToEnum = { 
		{ TEXT("Any"), PlayerClientWrappingTokenInput::AuthProviderEnum::Any },
		{ TEXT("Google"), PlayerClientWrappingTokenInput::AuthProviderEnum::Google },
		{ TEXT("Discord"), PlayerClientWrappingTokenInput::AuthProviderEnum::Discord },
		{ TEXT("Apple"), PlayerClientWrappingTokenInput::AuthProviderEnum::Apple }, };

	const auto Found = StringToEnum.Find(EnumAsString);
	if(Found)
		Value = *Found;

	return Found != nullptr;
}

bool PlayerClientWrappingTokenInput::EnumFromString(const FString& EnumAsString, PlayerClientWrappingTokenInput::AuthProviderEnum& EnumValue)
{
	return FromString(EnumAsString, EnumValue);
}

inline void WriteJsonValue(JsonWriter& Writer, const PlayerClientWrappingTokenInput::AuthProviderEnum& Value)
{
	WriteJsonValue(Writer, ToString(Value));
}

inline bool TryGetJsonValue(const TSharedPtr<FJsonValue>& JsonValue, PlayerClientWrappingTokenInput::AuthProviderEnum& Value)
{
	FString TmpValue;
	if (JsonValue->TryGetString(TmpValue))
	{
		if(FromString(TmpValue, Value))
			return true;
	}
	return false;
}

void PlayerClientWrappingTokenInput::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	Writer->WriteIdentifierPrefix(TEXT("amount")); WriteJsonValue(Writer, Amount);
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
	if (AuthProvider.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("authProvider")); WriteJsonValue(Writer, AuthProvider.GetValue());
	}
	Writer->WriteObjectEnd();
}

bool PlayerClientWrappingTokenInput::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("amount"), Amount);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("optimistic"), Optimistic);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("sponsor"), Sponsor);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("policyId"), PolicyId);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("chainId"), ChainId);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("operationProcessing"), OperationProcessing);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("authProvider"), AuthProvider);

	return ParseSuccess;
}

}
