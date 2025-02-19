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
#include "PlayerClientGetAssetsForContractBodyInputAttributesInner.h"

namespace OpenAPI
{

/*
 * PlayerClientGetAssetsForContractBodyInput
 *
 * 
 */
class PLAYERCLIENT_API PlayerClientGetAssetsForContractBodyInput : public Model
{
public:
    virtual ~PlayerClientGetAssetsForContractBodyInput() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	TOptional<FString> Continuation;
	TOptional<int64> ChainId;
	TOptional<int32> MinRarityRank;
	TOptional<int32> MaxRarityRank;
	TOptional<double> MinFloorAskPrice;
	TOptional<double> MaxFloorAskPrice;
	TOptional<bool> IncludeAttributes;
	TOptional<TArray<PlayerClientGetAssetsForContractBodyInputAttributesInner>> Attributes;
	enum class SortDirectionEnum
	{
		Asc,
		Desc,
  	};

	static FString EnumToString(const SortDirectionEnum& EnumValue);
	static bool EnumFromString(const FString& EnumAsString, SortDirectionEnum& EnumValue);
	TOptional<SortDirectionEnum> SortDirection;
	enum class SortByEnum
	{
		FloorAskPrice,
		TokenId,
		Rarity,
		UpdatedAt,
		MintedAt,
  	};

	static FString EnumToString(const SortByEnum& EnumValue);
	static bool EnumFromString(const FString& EnumAsString, SortByEnum& EnumValue);
	TOptional<SortByEnum> SortBy;
	TOptional<double> Limit;
};

}
