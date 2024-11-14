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

#include "PlayerClientPlayerOperationActionTransaction.h"

#include "PlayerClientModule.h"
#include "PlayerClientHelpers.h"

#include "Templates/SharedPointer.h"

namespace OpenAPI
{

inline FString ToString(const PlayerClientPlayerOperationActionTransaction::StatusEnum& Value)
{
	switch (Value)
	{
	case PlayerClientPlayerOperationActionTransaction::StatusEnum::Pending:
		return TEXT("Pending");
	case PlayerClientPlayerOperationActionTransaction::StatusEnum::_Signed:
		return TEXT("Signed");
	case PlayerClientPlayerOperationActionTransaction::StatusEnum::Rejected:
		return TEXT("Rejected");
	case PlayerClientPlayerOperationActionTransaction::StatusEnum::Executed:
		return TEXT("Executed");
	case PlayerClientPlayerOperationActionTransaction::StatusEnum::Error:
		return TEXT("Error");
	}

	UE_LOG(LogPlayerClient, Error, TEXT("Invalid PlayerClientPlayerOperationActionTransaction::StatusEnum Value (%d)"), (int)Value);
	return TEXT("");
}

FString PlayerClientPlayerOperationActionTransaction::EnumToString(const PlayerClientPlayerOperationActionTransaction::StatusEnum& EnumValue)
{
	return ToString(EnumValue);
}

inline bool FromString(const FString& EnumAsString, PlayerClientPlayerOperationActionTransaction::StatusEnum& Value)
{
	static TMap<FString, PlayerClientPlayerOperationActionTransaction::StatusEnum> StringToEnum = { 
		{ TEXT("Pending"), PlayerClientPlayerOperationActionTransaction::StatusEnum::Pending },
		{ TEXT("Signed"), PlayerClientPlayerOperationActionTransaction::StatusEnum::_Signed },
		{ TEXT("Rejected"), PlayerClientPlayerOperationActionTransaction::StatusEnum::Rejected },
		{ TEXT("Executed"), PlayerClientPlayerOperationActionTransaction::StatusEnum::Executed },
		{ TEXT("Error"), PlayerClientPlayerOperationActionTransaction::StatusEnum::Error }, };

	const auto Found = StringToEnum.Find(EnumAsString);
	if(Found)
		Value = *Found;

	return Found != nullptr;
}

bool PlayerClientPlayerOperationActionTransaction::EnumFromString(const FString& EnumAsString, PlayerClientPlayerOperationActionTransaction::StatusEnum& EnumValue)
{
	return FromString(EnumAsString, EnumValue);
}

inline void WriteJsonValue(JsonWriter& Writer, const PlayerClientPlayerOperationActionTransaction::StatusEnum& Value)
{
	WriteJsonValue(Writer, ToString(Value));
}

inline bool TryGetJsonValue(const TSharedPtr<FJsonValue>& JsonValue, PlayerClientPlayerOperationActionTransaction::StatusEnum& Value)
{
	FString TmpValue;
	if (JsonValue->TryGetString(TmpValue))
	{
		if(FromString(TmpValue, Value))
			return true;
	}
	return false;
}

void PlayerClientPlayerOperationActionTransaction::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	Writer->WriteIdentifierPrefix(TEXT("status")); WriteJsonValue(Writer, Status);
	Writer->WriteIdentifierPrefix(TEXT("id")); WriteJsonValue(Writer, Id);
	if (OpenfortId.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("openfortId")); WriteJsonValue(Writer, OpenfortId.GetValue());
	}
	Writer->WriteIdentifierPrefix(TEXT("sponsored")); WriteJsonValue(Writer, Sponsored);
	if (ActionId.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("actionId")); WriteJsonValue(Writer, ActionId.GetValue());
	}
	if (Hash.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("hash")); WriteJsonValue(Writer, Hash.GetValue());
	}
	Writer->WriteObjectEnd();
}

bool PlayerClientPlayerOperationActionTransaction::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("status"), Status);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("id"), Id);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("openfortId"), OpenfortId);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("sponsored"), Sponsored);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("actionId"), ActionId);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("hash"), Hash);

	return ParseSuccess;
}

}