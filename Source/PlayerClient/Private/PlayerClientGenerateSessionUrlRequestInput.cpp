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

#include "PlayerClientGenerateSessionUrlRequestInput.h"

#include "PlayerClientModule.h"
#include "PlayerClientHelpers.h"

#include "Templates/SharedPointer.h"

namespace OpenAPI
{

inline FString ToString(const PlayerClientGenerateSessionUrlRequestInput::AuthProviderEnum& Value)
{
	switch (Value)
	{
	case PlayerClientGenerateSessionUrlRequestInput::AuthProviderEnum::Any:
		return TEXT("Any");
	case PlayerClientGenerateSessionUrlRequestInput::AuthProviderEnum::Google:
		return TEXT("Google");
	case PlayerClientGenerateSessionUrlRequestInput::AuthProviderEnum::Discord:
		return TEXT("Discord");
	case PlayerClientGenerateSessionUrlRequestInput::AuthProviderEnum::Apple:
		return TEXT("Apple");
	}

	UE_LOG(LogPlayerClient, Error, TEXT("Invalid PlayerClientGenerateSessionUrlRequestInput::AuthProviderEnum Value (%d)"), (int)Value);
	return TEXT("");
}

FString PlayerClientGenerateSessionUrlRequestInput::EnumToString(const PlayerClientGenerateSessionUrlRequestInput::AuthProviderEnum& EnumValue)
{
	return ToString(EnumValue);
}

inline bool FromString(const FString& EnumAsString, PlayerClientGenerateSessionUrlRequestInput::AuthProviderEnum& Value)
{
	static TMap<FString, PlayerClientGenerateSessionUrlRequestInput::AuthProviderEnum> StringToEnum = { 
		{ TEXT("Any"), PlayerClientGenerateSessionUrlRequestInput::AuthProviderEnum::Any },
		{ TEXT("Google"), PlayerClientGenerateSessionUrlRequestInput::AuthProviderEnum::Google },
		{ TEXT("Discord"), PlayerClientGenerateSessionUrlRequestInput::AuthProviderEnum::Discord },
		{ TEXT("Apple"), PlayerClientGenerateSessionUrlRequestInput::AuthProviderEnum::Apple }, };

	const auto Found = StringToEnum.Find(EnumAsString);
	if(Found)
		Value = *Found;

	return Found != nullptr;
}

bool PlayerClientGenerateSessionUrlRequestInput::EnumFromString(const FString& EnumAsString, PlayerClientGenerateSessionUrlRequestInput::AuthProviderEnum& EnumValue)
{
	return FromString(EnumAsString, EnumValue);
}

inline void WriteJsonValue(JsonWriter& Writer, const PlayerClientGenerateSessionUrlRequestInput::AuthProviderEnum& Value)
{
	WriteJsonValue(Writer, ToString(Value));
}

inline bool TryGetJsonValue(const TSharedPtr<FJsonValue>& JsonValue, PlayerClientGenerateSessionUrlRequestInput::AuthProviderEnum& Value)
{
	FString TmpValue;
	if (JsonValue->TryGetString(TmpValue))
	{
		if(FromString(TmpValue, Value))
			return true;
	}
	return false;
}

void PlayerClientGenerateSessionUrlRequestInput::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	Writer->WriteIdentifierPrefix(TEXT("address")); WriteJsonValue(Writer, Address);
	if (SuggestedExpiry.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("suggestedExpiry")); WriteJsonValue(Writer, SuggestedExpiry.GetValue());
	}
	if (AuthProvider.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("authProvider")); WriteJsonValue(Writer, AuthProvider.GetValue());
	}
	if (ChainId.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("chainId")); WriteJsonValue(Writer, ChainId.GetValue());
	}
	Writer->WriteObjectEnd();
}

bool PlayerClientGenerateSessionUrlRequestInput::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("address"), Address);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("suggestedExpiry"), SuggestedExpiry);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("authProvider"), AuthProvider);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("chainId"), ChainId);

	return ParseSuccess;
}

}
