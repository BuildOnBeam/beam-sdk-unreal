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
 * PlayerClientCancelAssetListingRequestInput
 *
 * 
 */
class PLAYERCLIENT_API PlayerClientCancelAssetListingRequestInput : public Model
{
public:
    virtual ~PlayerClientCancelAssetListingRequestInput() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	TOptional<bool> Optimistic;
	TOptional<bool> Sponsor;
	TOptional<FString> PolicyId;
	enum class OperationProcessingEnum
	{
		SignOnly,
		Execute,
  	};

	static FString EnumToString(const OperationProcessingEnum& EnumValue);
	static bool EnumFromString(const FString& EnumAsString, OperationProcessingEnum& EnumValue);
	TOptional<OperationProcessingEnum> OperationProcessing;
};

}
