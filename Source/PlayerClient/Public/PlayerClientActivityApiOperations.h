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
#include "PlayerClientActivityApi.h"

#include "PlayerClientBeamErrorResponse.h"
#include "PlayerClientCommonActivityResponse.h"
#include "PlayerClientCommonAssetActivityRequestInput.h"
#include "PlayerClientCommonContractActivityRequestInput.h"
#include "PlayerClientCommonUserActivityRequestInput.h"

namespace OpenAPI
{

/* Get asset activity

*/
class PLAYERCLIENT_API PlayerClientActivityApi::GetAssetActivityRequest : public Request
{
public:
    virtual ~GetAssetActivityRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString AssetAddress;
	FString AssetId;
	PlayerClientCommonAssetActivityRequestInput PlayerClientCommonAssetActivityRequestInput;
};

class PLAYERCLIENT_API PlayerClientActivityApi::GetAssetActivityResponse : public Response
{
public:
    virtual ~GetAssetActivityResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientCommonActivityResponse Content;
};

/* Get contract activity

*/
class PLAYERCLIENT_API PlayerClientActivityApi::GetContractActivityRequest : public Request
{
public:
    virtual ~GetContractActivityRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString AssetAddress;
	PlayerClientCommonContractActivityRequestInput PlayerClientCommonContractActivityRequestInput;
};

class PLAYERCLIENT_API PlayerClientActivityApi::GetContractActivityResponse : public Response
{
public:
    virtual ~GetContractActivityResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientCommonActivityResponse Content;
};

/* Get user activity

*/
class PLAYERCLIENT_API PlayerClientActivityApi::GetUserActivityRequest : public Request
{
public:
    virtual ~GetUserActivityRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString EntityId;
	PlayerClientCommonUserActivityRequestInput PlayerClientCommonUserActivityRequestInput;
};

class PLAYERCLIENT_API PlayerClientActivityApi::GetUserActivityResponse : public Response
{
public:
    virtual ~GetUserActivityResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientCommonActivityResponse Content;
};

}
