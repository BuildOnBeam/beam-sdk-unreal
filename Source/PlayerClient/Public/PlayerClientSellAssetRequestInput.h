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

namespace OpenAPI
{

/*
 * PlayerClientSellAssetRequestInput
 *
 * 
 */
class PLAYERCLIENT_API PlayerClientSellAssetRequestInput : public Model
{
public:
    virtual ~PlayerClientSellAssetRequestInput() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	FString AssetAddress;
	FString AssetId;
	double Quantity;
	FString Price;
	/* Date time string with YYYY-MM-DDTHH:mm:ss.sssZ format or Unix timestamp in milliseconds */
	TOptional<FDateTime> StartTime;
	/* Date time string with YYYY-MM-DDTHH:mm:ss.sssZ format or Unix timestamp in milliseconds */
	TOptional<FDateTime> EndTime;
	enum class SellTypeEnum
	{
		FixedPrice,
		DescendingAuction,
		AscendingAuction,
		NotForSale,
  	};

	static FString EnumToString(const SellTypeEnum& EnumValue);
	static bool EnumFromString(const FString& EnumAsString, SellTypeEnum& EnumValue);
	SellTypeEnum SellType;
	enum class CurrencyEnum
	{
		Beam,
		Soph,
		Wbeam,
		Wsoph,
		Rat,
		Usdc,
  	};

	static FString EnumToString(const CurrencyEnum& EnumValue);
	static bool EnumFromString(const FString& EnumAsString, CurrencyEnum& EnumValue);
	TOptional<CurrencyEnum> Currency;
	TOptional<bool> Sponsor;
	TOptional<FString> PolicyId;
	TOptional<int64> ChainId;
	enum class OperationProcessingEnum
	{
		SignOnly,
		Execute,
  	};

	static FString EnumToString(const OperationProcessingEnum& EnumValue);
	static bool EnumFromString(const FString& EnumAsString, OperationProcessingEnum& EnumValue);
	TOptional<OperationProcessingEnum> OperationProcessing;
	TOptional<FString> OperationId;
};

}
