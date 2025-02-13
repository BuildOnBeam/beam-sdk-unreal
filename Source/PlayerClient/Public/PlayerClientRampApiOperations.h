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
#include "PlayerClientRampApi.h"
#include <string>
#include <stdexcept>
    
#include "PlayerClientBeamErrorResponse.h"
#include "PlayerClientCreateOnrampRequestInput.h"
#include "PlayerClientPlayerOperationResponse.h"

namespace OpenAPI
{

/* 

*/
class PLAYERCLIENT_API PlayerClientRampApi::CreateOnrampRequestRequest : public Request
{
public:
    virtual ~CreateOnrampRequestRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString EntityId;
	PlayerClientCreateOnrampRequestInput PlayerClientCreateOnrampRequestInput;
};

class PLAYERCLIENT_API PlayerClientRampApi::CreateOnrampRequestResponse : public Response
{
public:
    virtual ~CreateOnrampRequestResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientPlayerOperationResponse Content;
private:
    std::string GetHttpStatusCategory(EHttpResponseCodes::Type InHttpResponseCode);
};

}
