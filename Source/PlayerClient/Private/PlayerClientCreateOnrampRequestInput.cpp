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

#include "PlayerClientCreateOnrampRequestInput.h"

#include "PlayerClientModule.h"
#include "PlayerClientHelpers.h"

#include "Templates/SharedPointer.h"

namespace OpenAPI
{

inline FString ToString(const PlayerClientCreateOnrampRequestInput::TokenEnum& Value)
{
	switch (Value)
	{
	case PlayerClientCreateOnrampRequestInput::TokenEnum::Beam:
		return TEXT("BEAM");
	}

	UE_LOG(LogPlayerClient, Error, TEXT("Invalid PlayerClientCreateOnrampRequestInput::TokenEnum Value (%d)"), (int)Value);
	return TEXT("");
}

FString PlayerClientCreateOnrampRequestInput::EnumToString(const PlayerClientCreateOnrampRequestInput::TokenEnum& EnumValue)
{
	return ToString(EnumValue);
}

inline bool FromString(const FString& EnumAsString, PlayerClientCreateOnrampRequestInput::TokenEnum& Value)
{
	static TMap<FString, PlayerClientCreateOnrampRequestInput::TokenEnum> StringToEnum = { 
		{ TEXT("BEAM"), PlayerClientCreateOnrampRequestInput::TokenEnum::Beam }, };

	const auto Found = StringToEnum.Find(EnumAsString);
	if(Found)
		Value = *Found;

	return Found != nullptr;
}

bool PlayerClientCreateOnrampRequestInput::EnumFromString(const FString& EnumAsString, PlayerClientCreateOnrampRequestInput::TokenEnum& EnumValue)
{
	return FromString(EnumAsString, EnumValue);
}

inline void WriteJsonValue(JsonWriter& Writer, const PlayerClientCreateOnrampRequestInput::TokenEnum& Value)
{
	WriteJsonValue(Writer, ToString(Value));
}

inline bool TryGetJsonValue(const TSharedPtr<FJsonValue>& JsonValue, PlayerClientCreateOnrampRequestInput::TokenEnum& Value)
{
	FString TmpValue;
	if (JsonValue->TryGetString(TmpValue))
	{
		if(FromString(TmpValue, Value))
			return true;
	}
	return false;
}

inline FString ToString(const PlayerClientCreateOnrampRequestInput::PaymentCurrencyEnum& Value)
{
	switch (Value)
	{
	case PlayerClientCreateOnrampRequestInput::PaymentCurrencyEnum::Usd:
		return TEXT("USD");
	case PlayerClientCreateOnrampRequestInput::PaymentCurrencyEnum::Eur:
		return TEXT("EUR");
	}

	UE_LOG(LogPlayerClient, Error, TEXT("Invalid PlayerClientCreateOnrampRequestInput::PaymentCurrencyEnum Value (%d)"), (int)Value);
	return TEXT("");
}

FString PlayerClientCreateOnrampRequestInput::EnumToString(const PlayerClientCreateOnrampRequestInput::PaymentCurrencyEnum& EnumValue)
{
	return ToString(EnumValue);
}

inline bool FromString(const FString& EnumAsString, PlayerClientCreateOnrampRequestInput::PaymentCurrencyEnum& Value)
{
	static TMap<FString, PlayerClientCreateOnrampRequestInput::PaymentCurrencyEnum> StringToEnum = { 
		{ TEXT("USD"), PlayerClientCreateOnrampRequestInput::PaymentCurrencyEnum::Usd },
		{ TEXT("EUR"), PlayerClientCreateOnrampRequestInput::PaymentCurrencyEnum::Eur }, };

	const auto Found = StringToEnum.Find(EnumAsString);
	if(Found)
		Value = *Found;

	return Found != nullptr;
}

bool PlayerClientCreateOnrampRequestInput::EnumFromString(const FString& EnumAsString, PlayerClientCreateOnrampRequestInput::PaymentCurrencyEnum& EnumValue)
{
	return FromString(EnumAsString, EnumValue);
}

inline void WriteJsonValue(JsonWriter& Writer, const PlayerClientCreateOnrampRequestInput::PaymentCurrencyEnum& Value)
{
	WriteJsonValue(Writer, ToString(Value));
}

inline bool TryGetJsonValue(const TSharedPtr<FJsonValue>& JsonValue, PlayerClientCreateOnrampRequestInput::PaymentCurrencyEnum& Value)
{
	FString TmpValue;
	if (JsonValue->TryGetString(TmpValue))
	{
		if(FromString(TmpValue, Value))
			return true;
	}
	return false;
}

void PlayerClientCreateOnrampRequestInput::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	if (Token.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("token")); WriteJsonValue(Writer, Token.GetValue());
	}
	if (TokenAmount.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("tokenAmount")); WriteJsonValue(Writer, TokenAmount.GetValue());
	}
	if (FiatAmount.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("fiatAmount")); WriteJsonValue(Writer, FiatAmount.GetValue());
	}
	if (PaymentCurrency.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("paymentCurrency")); WriteJsonValue(Writer, PaymentCurrency.GetValue());
	}
	if (ChainId.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("chainId")); WriteJsonValue(Writer, ChainId.GetValue());
	}
	Writer->WriteObjectEnd();
}

bool PlayerClientCreateOnrampRequestInput::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("token"), Token);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("tokenAmount"), TokenAmount);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("fiatAmount"), FiatAmount);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("paymentCurrency"), PaymentCurrency);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("chainId"), ChainId);

	return ParseSuccess;
}

}