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
#include "PlayerClientGetUserNativeCurrencyResponseNativeTokenBalance.h"

namespace OpenAPI
{

/*
 * PlayerClientGetUserNativeCurrencyResponse
 *
 * 
 */
class PLAYERCLIENT_API PlayerClientGetUserNativeCurrencyResponse : public Model
{
public:
    virtual ~PlayerClientGetUserNativeCurrencyResponse() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	PlayerClientGetUserNativeCurrencyResponseNativeTokenBalance NativeTokenBalance;
};

}