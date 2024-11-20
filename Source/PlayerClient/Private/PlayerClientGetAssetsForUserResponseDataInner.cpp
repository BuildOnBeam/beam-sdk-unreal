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

#include "PlayerClientGetAssetsForUserResponseDataInner.h"

#include "PlayerClientModule.h"
#include "PlayerClientHelpers.h"

#include "Templates/SharedPointer.h"

namespace OpenAPI
{

inline FString ToString(const PlayerClientGetAssetsForUserResponseDataInner::RarityEnum& Value)
{
	switch (Value)
	{
	case PlayerClientGetAssetsForUserResponseDataInner::RarityEnum::Common:
		return TEXT("Common");
	case PlayerClientGetAssetsForUserResponseDataInner::RarityEnum::Uncommon:
		return TEXT("Uncommon");
	case PlayerClientGetAssetsForUserResponseDataInner::RarityEnum::Rare:
		return TEXT("Rare");
	case PlayerClientGetAssetsForUserResponseDataInner::RarityEnum::VeryRare:
		return TEXT("VeryRare");
	case PlayerClientGetAssetsForUserResponseDataInner::RarityEnum::ExtremelyRare:
		return TEXT("ExtremelyRare");
	}

	UE_LOG(LogPlayerClient, Error, TEXT("Invalid PlayerClientGetAssetsForUserResponseDataInner::RarityEnum Value (%d)"), (int)Value);
	return TEXT("");
}

FString PlayerClientGetAssetsForUserResponseDataInner::EnumToString(const PlayerClientGetAssetsForUserResponseDataInner::RarityEnum& EnumValue)
{
	return ToString(EnumValue);
}

inline bool FromString(const FString& EnumAsString, PlayerClientGetAssetsForUserResponseDataInner::RarityEnum& Value)
{
	static TMap<FString, PlayerClientGetAssetsForUserResponseDataInner::RarityEnum> StringToEnum = { 
		{ TEXT("Common"), PlayerClientGetAssetsForUserResponseDataInner::RarityEnum::Common },
		{ TEXT("Uncommon"), PlayerClientGetAssetsForUserResponseDataInner::RarityEnum::Uncommon },
		{ TEXT("Rare"), PlayerClientGetAssetsForUserResponseDataInner::RarityEnum::Rare },
		{ TEXT("VeryRare"), PlayerClientGetAssetsForUserResponseDataInner::RarityEnum::VeryRare },
		{ TEXT("ExtremelyRare"), PlayerClientGetAssetsForUserResponseDataInner::RarityEnum::ExtremelyRare }, };

	const auto Found = StringToEnum.Find(EnumAsString);
	if(Found)
		Value = *Found;

	return Found != nullptr;
}

bool PlayerClientGetAssetsForUserResponseDataInner::EnumFromString(const FString& EnumAsString, PlayerClientGetAssetsForUserResponseDataInner::RarityEnum& EnumValue)
{
	return FromString(EnumAsString, EnumValue);
}

inline void WriteJsonValue(JsonWriter& Writer, const PlayerClientGetAssetsForUserResponseDataInner::RarityEnum& Value)
{
	WriteJsonValue(Writer, ToString(Value));
}

inline bool TryGetJsonValue(const TSharedPtr<FJsonValue>& JsonValue, PlayerClientGetAssetsForUserResponseDataInner::RarityEnum& Value)
{
	FString TmpValue;
	if (JsonValue->TryGetString(TmpValue))
	{
		if(FromString(TmpValue, Value))
			return true;
	}
	return false;
}

void PlayerClientGetAssetsForUserResponseDataInner::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	Writer->WriteIdentifierPrefix(TEXT("name")); WriteJsonValue(Writer, Name);
	Writer->WriteIdentifierPrefix(TEXT("imageUrl")); WriteJsonValue(Writer, ImageUrl);
	Writer->WriteIdentifierPrefix(TEXT("assetType")); WriteJsonValue(Writer, AssetType);
	Writer->WriteIdentifierPrefix(TEXT("assetAddress")); WriteJsonValue(Writer, AssetAddress);
	Writer->WriteIdentifierPrefix(TEXT("assetId")); WriteJsonValue(Writer, AssetId);
	Writer->WriteIdentifierPrefix(TEXT("supply")); WriteJsonValue(Writer, Supply);
	if (Rarity.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("rarity")); WriteJsonValue(Writer, Rarity.GetValue());
	}
	if (RarityScore.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("rarityScore")); WriteJsonValue(Writer, RarityScore.GetValue());
	}
	if (UpdatedAt.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("updatedAt")); WriteJsonValue(Writer, UpdatedAt.GetValue());
	}
	if (MintedAt.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("mintedAt")); WriteJsonValue(Writer, MintedAt.GetValue());
	}
	if (Attributes.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("attributes")); WriteJsonValue(Writer, Attributes.GetValue());
	}
	if (ChainId.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("chainId")); WriteJsonValue(Writer, ChainId.GetValue());
	}
	Writer->WriteIdentifierPrefix(TEXT("ownedQuantity")); WriteJsonValue(Writer, OwnedQuantity);
	Writer->WriteObjectEnd();
}

bool PlayerClientGetAssetsForUserResponseDataInner::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("name"), Name);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("imageUrl"), ImageUrl);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("assetType"), AssetType);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("assetAddress"), AssetAddress);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("assetId"), AssetId);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("supply"), Supply);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("rarity"), Rarity);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("rarityScore"), RarityScore);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("updatedAt"), UpdatedAt);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("mintedAt"), MintedAt);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("attributes"), Attributes);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("chainId"), ChainId);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("ownedQuantity"), OwnedQuantity);

	return ParseSuccess;
}

}
