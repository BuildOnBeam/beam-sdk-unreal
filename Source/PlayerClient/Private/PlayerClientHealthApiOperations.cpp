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

#include "PlayerClientHealthApiOperations.h"

#include "PlayerClientModule.h"
#include "PlayerClientHelpers.h"

#include "Dom/JsonObject.h"
#include "Templates/SharedPointer.h"
#include "HttpModule.h"
#include "PlatformHttp.h"

namespace OpenAPI
{

FString PlayerClientHealthApi::CheckRequest::ComputePath() const
{
	FString Path(TEXT("/v1/health/services"));
	return Path;
}

void PlayerClientHealthApi::CheckRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("application/json") };

	HttpRequest->SetVerb(TEXT("GET"));

}

void PlayerClientHealthApi::CheckResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);
	switch ((int)InHttpResponseCode)
	{
	case 200:
		SetResponseString(TEXT("The Health Check is successful"));
		break;
	case 503:
		SetResponseString(TEXT("The Health Check is not successful"));
		break;
	case 4XX:
		SetResponseString(TEXT(""));
		break;
	case 5XX:
		SetResponseString(TEXT(""));
		break;
	}
}

bool PlayerClientHealthApi::CheckResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

}
