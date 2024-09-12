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

#include "PlayerClientCreateAssetOfferRequestInput.h"

#include "PlayerClientModule.h"
#include "PlayerClientHelpers.h"

#include "Templates/SharedPointer.h"

namespace OpenAPI
{

inline FString ToString(const PlayerClientCreateAssetOfferRequestInput::CurrencyEnum& Value)
{
	switch (Value)
	{
	case PlayerClientCreateAssetOfferRequestInput::CurrencyEnum::Wbeam:
		return TEXT("WBEAM");
	case PlayerClientCreateAssetOfferRequestInput::CurrencyEnum::Wimx:
		return TEXT("WIMX");
	case PlayerClientCreateAssetOfferRequestInput::CurrencyEnum::Wsoph:
		return TEXT("WSOPH");
	case PlayerClientCreateAssetOfferRequestInput::CurrencyEnum::Rat:
		return TEXT("RAT");
	case PlayerClientCreateAssetOfferRequestInput::CurrencyEnum::Usdc:
		return TEXT("USDC");
	}

	UE_LOG(LogPlayerClient, Error, TEXT("Invalid PlayerClientCreateAssetOfferRequestInput::CurrencyEnum Value (%d)"), (int)Value);
	return TEXT("");
}

FString PlayerClientCreateAssetOfferRequestInput::EnumToString(const PlayerClientCreateAssetOfferRequestInput::CurrencyEnum& EnumValue)
{
	return ToString(EnumValue);
}

inline bool FromString(const FString& EnumAsString, PlayerClientCreateAssetOfferRequestInput::CurrencyEnum& Value)
{
	static TMap<FString, PlayerClientCreateAssetOfferRequestInput::CurrencyEnum> StringToEnum = { 
		{ TEXT("WBEAM"), PlayerClientCreateAssetOfferRequestInput::CurrencyEnum::Wbeam },
		{ TEXT("WIMX"), PlayerClientCreateAssetOfferRequestInput::CurrencyEnum::Wimx },
		{ TEXT("WSOPH"), PlayerClientCreateAssetOfferRequestInput::CurrencyEnum::Wsoph },
		{ TEXT("RAT"), PlayerClientCreateAssetOfferRequestInput::CurrencyEnum::Rat },
		{ TEXT("USDC"), PlayerClientCreateAssetOfferRequestInput::CurrencyEnum::Usdc }, };

	const auto Found = StringToEnum.Find(EnumAsString);
	if(Found)
		Value = *Found;

	return Found != nullptr;
}

bool PlayerClientCreateAssetOfferRequestInput::EnumFromString(const FString& EnumAsString, PlayerClientCreateAssetOfferRequestInput::CurrencyEnum& EnumValue)
{
	return FromString(EnumAsString, EnumValue);
}

inline void WriteJsonValue(JsonWriter& Writer, const PlayerClientCreateAssetOfferRequestInput::CurrencyEnum& Value)
{
	WriteJsonValue(Writer, ToString(Value));
}

inline bool TryGetJsonValue(const TSharedPtr<FJsonValue>& JsonValue, PlayerClientCreateAssetOfferRequestInput::CurrencyEnum& Value)
{
	FString TmpValue;
	if (JsonValue->TryGetString(TmpValue))
	{
		if(FromString(TmpValue, Value))
			return true;
	}
	return false;
}

inline FString ToString(const PlayerClientCreateAssetOfferRequestInput::OperationProcessingEnum& Value)
{
	switch (Value)
	{
	case PlayerClientCreateAssetOfferRequestInput::OperationProcessingEnum::SignOnly:
		return TEXT("SignOnly");
	case PlayerClientCreateAssetOfferRequestInput::OperationProcessingEnum::Execute:
		return TEXT("Execute");
	}

	UE_LOG(LogPlayerClient, Error, TEXT("Invalid PlayerClientCreateAssetOfferRequestInput::OperationProcessingEnum Value (%d)"), (int)Value);
	return TEXT("");
}

FString PlayerClientCreateAssetOfferRequestInput::EnumToString(const PlayerClientCreateAssetOfferRequestInput::OperationProcessingEnum& EnumValue)
{
	return ToString(EnumValue);
}

inline bool FromString(const FString& EnumAsString, PlayerClientCreateAssetOfferRequestInput::OperationProcessingEnum& Value)
{
	static TMap<FString, PlayerClientCreateAssetOfferRequestInput::OperationProcessingEnum> StringToEnum = { 
		{ TEXT("SignOnly"), PlayerClientCreateAssetOfferRequestInput::OperationProcessingEnum::SignOnly },
		{ TEXT("Execute"), PlayerClientCreateAssetOfferRequestInput::OperationProcessingEnum::Execute }, };

	const auto Found = StringToEnum.Find(EnumAsString);
	if(Found)
		Value = *Found;

	return Found != nullptr;
}

bool PlayerClientCreateAssetOfferRequestInput::EnumFromString(const FString& EnumAsString, PlayerClientCreateAssetOfferRequestInput::OperationProcessingEnum& EnumValue)
{
	return FromString(EnumAsString, EnumValue);
}

inline void WriteJsonValue(JsonWriter& Writer, const PlayerClientCreateAssetOfferRequestInput::OperationProcessingEnum& Value)
{
	WriteJsonValue(Writer, ToString(Value));
}

inline bool TryGetJsonValue(const TSharedPtr<FJsonValue>& JsonValue, PlayerClientCreateAssetOfferRequestInput::OperationProcessingEnum& Value)
{
	FString TmpValue;
	if (JsonValue->TryGetString(TmpValue))
	{
		if(FromString(TmpValue, Value))
			return true;
	}
	return false;
}

void PlayerClientCreateAssetOfferRequestInput::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	Writer->WriteIdentifierPrefix(TEXT("assetAddress")); WriteJsonValue(Writer, AssetAddress);
	Writer->WriteIdentifierPrefix(TEXT("assetId")); WriteJsonValue(Writer, AssetId);
	Writer->WriteIdentifierPrefix(TEXT("quantity")); WriteJsonValue(Writer, Quantity);
	Writer->WriteIdentifierPrefix(TEXT("price")); WriteJsonValue(Writer, Price);
	if (StartTime.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("startTime")); WriteJsonValue(Writer, StartTime.GetValue());
	}
	if (EndTime.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("endTime")); WriteJsonValue(Writer, EndTime.GetValue());
	}
	if (Currency.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("currency")); WriteJsonValue(Writer, Currency.GetValue());
	}
	if (ChainId.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("chainId")); WriteJsonValue(Writer, ChainId.GetValue());
	}
	if (OperationProcessing.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("operationProcessing")); WriteJsonValue(Writer, OperationProcessing.GetValue());
	}
	if (OperationId.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("operationId")); WriteJsonValue(Writer, OperationId.GetValue());
	}
	Writer->WriteObjectEnd();
}

bool PlayerClientCreateAssetOfferRequestInput::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("assetAddress"), AssetAddress);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("assetId"), AssetId);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("quantity"), Quantity);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("price"), Price);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("startTime"), StartTime);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("endTime"), EndTime);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("currency"), Currency);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("chainId"), ChainId);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("operationProcessing"), OperationProcessing);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("operationId"), OperationId);

	return ParseSuccess;
}

}
