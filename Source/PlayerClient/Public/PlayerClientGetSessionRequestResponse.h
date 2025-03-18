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
 * PlayerClientGetSessionRequestResponse
 *
 * 
 */
class PLAYERCLIENT_API PlayerClientGetSessionRequestResponse : public Model
{
public:
    virtual ~PlayerClientGetSessionRequestResponse() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	enum class StatusEnum
	{
		Pending,
		Accepted,
		Error,
  	};

	static FString EnumToString(const StatusEnum& EnumValue);
	static bool EnumFromString(const FString& EnumAsString, StatusEnum& EnumValue);
	StatusEnum Status;
	FString Id;
	FDateTime CreatedAt;
	TOptional<FDateTime> UpdatedAt;
	int64 ChainId = 0;
	TOptional<FString> OpenfortId;
	FString Address;
	TArray<FString> Contracts;
};

}
