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
 * PlayerClientRevokeSessionRequestInput
 *
 * 
 */
class PLAYERCLIENT_API PlayerClientRevokeSessionRequestInput : public Model
{
public:
    virtual ~PlayerClientRevokeSessionRequestInput() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	FString Address;
	TOptional<FString> OperationId;
	enum class OperationProcessingEnum
	{
		SignOnly,
		Execute,
  	};

	static FString EnumToString(const OperationProcessingEnum& EnumValue);
	static bool EnumFromString(const FString& EnumAsString, OperationProcessingEnum& EnumValue);
	TOptional<OperationProcessingEnum> OperationProcessing;
	TOptional<int64> ChainId;
};

}
