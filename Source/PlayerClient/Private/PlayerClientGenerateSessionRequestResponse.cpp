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

#include "PlayerClientGenerateSessionRequestResponse.h"

#include "PlayerClientModule.h"
#include "PlayerClientHelpers.h"

#include "Templates/SharedPointer.h"

namespace OpenAPI
{

inline FString ToString(const PlayerClientGenerateSessionRequestResponse::StatusEnum& Value)
{
	switch (Value)
	{
	case PlayerClientGenerateSessionRequestResponse::StatusEnum::Pending:
		return TEXT("Pending");
	case PlayerClientGenerateSessionRequestResponse::StatusEnum::Accepted:
		return TEXT("Accepted");
	case PlayerClientGenerateSessionRequestResponse::StatusEnum::Error:
		return TEXT("Error");
	}

	UE_LOG(LogPlayerClient, Error, TEXT("Invalid PlayerClientGenerateSessionRequestResponse::StatusEnum Value (%d)"), (int)Value);
	return TEXT("");
}

FString PlayerClientGenerateSessionRequestResponse::EnumToString(const PlayerClientGenerateSessionRequestResponse::StatusEnum& EnumValue)
{
	return ToString(EnumValue);
}

inline bool FromString(const FString& EnumAsString, PlayerClientGenerateSessionRequestResponse::StatusEnum& Value)
{
	static TMap<FString, PlayerClientGenerateSessionRequestResponse::StatusEnum> StringToEnum = { 
		{ TEXT("Pending"), PlayerClientGenerateSessionRequestResponse::StatusEnum::Pending },
		{ TEXT("Accepted"), PlayerClientGenerateSessionRequestResponse::StatusEnum::Accepted },
		{ TEXT("Error"), PlayerClientGenerateSessionRequestResponse::StatusEnum::Error }, };

	const auto Found = StringToEnum.Find(EnumAsString);
	if(Found)
		Value = *Found;

	return Found != nullptr;
}

bool PlayerClientGenerateSessionRequestResponse::EnumFromString(const FString& EnumAsString, PlayerClientGenerateSessionRequestResponse::StatusEnum& EnumValue)
{
	return FromString(EnumAsString, EnumValue);
}

inline void WriteJsonValue(JsonWriter& Writer, const PlayerClientGenerateSessionRequestResponse::StatusEnum& Value)
{
	WriteJsonValue(Writer, ToString(Value));
}

inline bool TryGetJsonValue(const TSharedPtr<FJsonValue>& JsonValue, PlayerClientGenerateSessionRequestResponse::StatusEnum& Value)
{
	FString TmpValue;
	if (JsonValue->TryGetString(TmpValue))
	{
		if(FromString(TmpValue, Value))
			return true;
	}
	return false;
}

inline FString ToString(const PlayerClientGenerateSessionRequestResponse::AuthProviderEnum& Value)
{
	switch (Value)
	{
	case PlayerClientGenerateSessionRequestResponse::AuthProviderEnum::Any:
		return TEXT("Any");
	case PlayerClientGenerateSessionRequestResponse::AuthProviderEnum::Google:
		return TEXT("Google");
	case PlayerClientGenerateSessionRequestResponse::AuthProviderEnum::Discord:
		return TEXT("Discord");
	case PlayerClientGenerateSessionRequestResponse::AuthProviderEnum::Apple:
		return TEXT("Apple");
	}

	UE_LOG(LogPlayerClient, Error, TEXT("Invalid PlayerClientGenerateSessionRequestResponse::AuthProviderEnum Value (%d)"), (int)Value);
	return TEXT("");
}

FString PlayerClientGenerateSessionRequestResponse::EnumToString(const PlayerClientGenerateSessionRequestResponse::AuthProviderEnum& EnumValue)
{
	return ToString(EnumValue);
}

inline bool FromString(const FString& EnumAsString, PlayerClientGenerateSessionRequestResponse::AuthProviderEnum& Value)
{
	static TMap<FString, PlayerClientGenerateSessionRequestResponse::AuthProviderEnum> StringToEnum = { 
		{ TEXT("Any"), PlayerClientGenerateSessionRequestResponse::AuthProviderEnum::Any },
		{ TEXT("Google"), PlayerClientGenerateSessionRequestResponse::AuthProviderEnum::Google },
		{ TEXT("Discord"), PlayerClientGenerateSessionRequestResponse::AuthProviderEnum::Discord },
		{ TEXT("Apple"), PlayerClientGenerateSessionRequestResponse::AuthProviderEnum::Apple }, };

	const auto Found = StringToEnum.Find(EnumAsString);
	if(Found)
		Value = *Found;

	return Found != nullptr;
}

bool PlayerClientGenerateSessionRequestResponse::EnumFromString(const FString& EnumAsString, PlayerClientGenerateSessionRequestResponse::AuthProviderEnum& EnumValue)
{
	return FromString(EnumAsString, EnumValue);
}

inline void WriteJsonValue(JsonWriter& Writer, const PlayerClientGenerateSessionRequestResponse::AuthProviderEnum& Value)
{
	WriteJsonValue(Writer, ToString(Value));
}

inline bool TryGetJsonValue(const TSharedPtr<FJsonValue>& JsonValue, PlayerClientGenerateSessionRequestResponse::AuthProviderEnum& Value)
{
	FString TmpValue;
	if (JsonValue->TryGetString(TmpValue))
	{
		if(FromString(TmpValue, Value))
			return true;
	}
	return false;
}

void PlayerClientGenerateSessionRequestResponse::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	Writer->WriteIdentifierPrefix(TEXT("status")); WriteJsonValue(Writer, Status);
	Writer->WriteIdentifierPrefix(TEXT("authProvider")); WriteJsonValue(Writer, AuthProvider);
	Writer->WriteIdentifierPrefix(TEXT("id")); WriteJsonValue(Writer, Id);
	Writer->WriteIdentifierPrefix(TEXT("createdAt")); WriteJsonValue(Writer, CreatedAt);
	if (UpdatedAt.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("updatedAt")); WriteJsonValue(Writer, UpdatedAt.GetValue());
	}
	if (EntityId.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("entityId")); WriteJsonValue(Writer, EntityId.GetValue());
	}
	Writer->WriteIdentifierPrefix(TEXT("gameId")); WriteJsonValue(Writer, GameId);
	Writer->WriteIdentifierPrefix(TEXT("chainId")); WriteJsonValue(Writer, ChainId);
	if (OpenfortId.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("openfortId")); WriteJsonValue(Writer, OpenfortId.GetValue());
	}
	Writer->WriteIdentifierPrefix(TEXT("address")); WriteJsonValue(Writer, Address);
	Writer->WriteIdentifierPrefix(TEXT("contracts")); WriteJsonValue(Writer, Contracts);
	Writer->WriteIdentifierPrefix(TEXT("url")); WriteJsonValue(Writer, Url);
	Writer->WriteObjectEnd();
}

bool PlayerClientGenerateSessionRequestResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("status"), Status);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("authProvider"), AuthProvider);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("id"), Id);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("createdAt"), CreatedAt);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("updatedAt"), UpdatedAt);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("entityId"), EntityId);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("gameId"), GameId);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("chainId"), ChainId);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("openfortId"), OpenfortId);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("address"), Address);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("contracts"), Contracts);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("url"), Url);

	return ParseSuccess;
}

}
