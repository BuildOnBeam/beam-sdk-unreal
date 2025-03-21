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
#include "PlayerClientContractApi.h"
#include <string>
#include <stdexcept>
    
#include "PlayerClientBeamErrorResponse.h"
#include "PlayerClientReadContractRequest.h"
#include "PlayerClientReadContractResonse.h"

namespace OpenAPI
{

/* Calls a readable contract function

*/
class PLAYERCLIENT_API PlayerClientContractApi::ReadContractRequest : public Request
{
public:
    virtual ~ReadContractRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString ContractAddress;
	PlayerClientReadContractRequest PlayerClientReadContractRequest;
};

class PLAYERCLIENT_API PlayerClientContractApi::ReadContractResponse : public Response
{
public:
    virtual ~ReadContractResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientReadContractResonse Content;
private:
    FString GetHttpStatusCategory(EHttpResponseCodes::Type InHttpResponseCode);
};

}
