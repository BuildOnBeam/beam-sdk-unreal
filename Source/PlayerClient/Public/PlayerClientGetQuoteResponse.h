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
 * PlayerClientGetQuoteResponse
 *
 * 
 */
class PLAYERCLIENT_API PlayerClientGetQuoteResponse : public Model
{
public:
    virtual ~PlayerClientGetQuoteResponse() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	FString TokenIn;
	FString TokenOut;
	FString AmountIn;
	FString AmountOut;
};

}