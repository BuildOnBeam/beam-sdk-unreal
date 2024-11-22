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

#pragma once

#include "PlayerClientBaseModel.h"
#include "PlayerClientGetAssetsForUserResponseDataInnerAttributesInner.h"

namespace OpenAPI
{

/*
 * PlayerClientGetAssetsForContractResponseDataInner
 *
 * 
 */
class PLAYERCLIENT_API PlayerClientGetAssetsForContractResponseDataInner : public Model
{
public:
    virtual ~PlayerClientGetAssetsForContractResponseDataInner() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	FString Name;
	FString ImageUrl;
	FString AssetType;
	FString AssetAddress;
	FString AssetId;
	double Supply;
	enum class RarityEnum
	{
		Common,
		Uncommon,
		Rare,
		VeryRare,
		ExtremelyRare,
  	};

	static FString EnumToString(const RarityEnum& EnumValue);
	static bool EnumFromString(const FString& EnumAsString, RarityEnum& EnumValue);
	TOptional<RarityEnum> Rarity;
	TOptional<double> RarityScore;
	TOptional<FDateTime> UpdatedAt;
	TOptional<FDateTime> MintedAt;
	TOptional<TArray<PlayerClientGetAssetsForUserResponseDataInnerAttributesInner>> Attributes;
	TOptional<int64> ChainId;
};

}
