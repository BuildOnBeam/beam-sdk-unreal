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
#include "PlayerClientConnectorApi.h"

#include "PlayerClientBeamErrorResponse.h"
#include "PlayerClientCreateConnectionRequestInput.h"
#include "PlayerClientCreateConnectionRequestResponse.h"
#include "PlayerClientGetConnectionRequestResponse.h"

namespace OpenAPI
{

/* 

*/
class PLAYERCLIENT_API PlayerClientConnectorApi::CreateConnectionRequestRequest : public Request
{
public:
    virtual ~CreateConnectionRequestRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	PlayerClientCreateConnectionRequestInput PlayerClientCreateConnectionRequestInput;
};

class PLAYERCLIENT_API PlayerClientConnectorApi::CreateConnectionRequestResponse : public Response
{
public:
    virtual ~CreateConnectionRequestResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientCreateConnectionRequestResponse Content;
};

/* 

*/
class PLAYERCLIENT_API PlayerClientConnectorApi::GetConnectionRequestRequest : public Request
{
public:
    virtual ~GetConnectionRequestRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString RequestId;
};

class PLAYERCLIENT_API PlayerClientConnectorApi::GetConnectionRequestResponse : public Response
{
public:
    virtual ~GetConnectionRequestResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientGetConnectionRequestResponse Content;
};

}
