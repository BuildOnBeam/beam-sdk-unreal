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
#include "PlayerClientGetOwnersResponsePagination.h"
#include "PlayerClientGetTransactionsResponseDataInner.h"

namespace OpenAPI
{

/*
 * PlayerClientGetTransactionsResponse
 *
 * 
 */
class PLAYERCLIENT_API PlayerClientGetTransactionsResponse : public Model
{
public:
    virtual ~PlayerClientGetTransactionsResponse() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	TArray<PlayerClientGetTransactionsResponseDataInner> Data;
	PlayerClientGetOwnersResponsePagination Pagination;
};

}