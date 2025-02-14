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

#include "PlayerClientSessionsApiOperations.h"

#include "PlayerClientModule.h"
#include "PlayerClientHelpers.h"

#include <string>
#include <stdexcept>

#include "Dom/JsonObject.h"
#include "Templates/SharedPointer.h"
#include "HttpModule.h"
#include "PlatformHttp.h"

namespace OpenAPI
{

FString PlayerClientSessionsApi::CreateSessionRequestRequest::ComputePath() const
{
	TMap<FString, FStringFormatArg> PathParams = { 
	{ TEXT("entityId"), FStringFormatArg(ToUrlString(EntityId)) } };

	FString Path = FString::Format(TEXT("/v1/player/sessions/users/{entityId}/request"), PathParams);

	return Path;
}

void PlayerClientSessionsApi::CreateSessionRequestRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = { TEXT("application/json") };
	//static const TArray<FString> Produces = { TEXT("application/json") };

	HttpRequest->SetVerb(TEXT("POST"));

	// Default to Json Body request
	if (Consumes.Num() == 0 || Consumes.Contains(TEXT("application/json")))
	{
		// Body parameters
		FString JsonBody;
		JsonWriter Writer = TJsonWriterFactory<>::Create(&JsonBody);

		WriteJsonValue(Writer, PlayerClientGenerateSessionUrlRequestInput);
		Writer->Close();

		HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
		HttpRequest->SetContentAsString(JsonBody);
	}
	else if (Consumes.Contains(TEXT("multipart/form-data")))
	{
		UE_LOG(LogPlayerClient, Error, TEXT("Body parameter (PlayerClientGenerateSessionUrlRequestInput) was ignored, not supported in multipart form"));
	}
	else if (Consumes.Contains(TEXT("application/x-www-form-urlencoded")))
	{
		UE_LOG(LogPlayerClient, Error, TEXT("Body parameter (PlayerClientGenerateSessionUrlRequestInput) was ignored, not supported in urlencoded requests"));
	}
	else
	{
		UE_LOG(LogPlayerClient, Error, TEXT("Request ContentType not supported (%s)"), *FString::Join(Consumes, TEXT(",")));
	}
}

void PlayerClientSessionsApi::CreateSessionRequestResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);

        if ((int)InHttpResponseCode == 200)
        {
            SetResponseString(TEXT(""));
            return;
        }
        if (GetHttpStatusCategory(InHttpResponseCode) == "4XX")
        {
            SetResponseString(TEXT(""));
            return;
        }
        if (GetHttpStatusCategory(InHttpResponseCode) == "5XX")
        {
            SetResponseString(TEXT(""));
            return;
        }
}

FString PlayerClientSessionsApi::CreateSessionRequestResponse::GetHttpStatusCategory(EHttpResponseCodes::Type InHttpResponseCode) {
    int statusCode = (int)InHttpResponseCode;

    // Ensure the input is a valid 3-digit HTTP status code
    if (statusCode < 100 || statusCode > 599) {
        throw std::invalid_argument("Invalid HTTP status code. Must be between 100 and 599.");
    }

    // Extract the first digit and append "XX"
    int firstDigit = statusCode / 100;
    return FString::Printf(TEXT("%dXX"), firstDigit);
}

bool PlayerClientSessionsApi::CreateSessionRequestResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

FString PlayerClientSessionsApi::GetActiveSessionRequest::ComputePath() const
{
	TMap<FString, FStringFormatArg> PathParams = { 
	{ TEXT("entityId"), FStringFormatArg(ToUrlString(EntityId)) },
	{ TEXT("accountAddress"), FStringFormatArg(ToUrlString(AccountAddress)) } };

	FString Path = FString::Format(TEXT("/v1/player/sessions/users/{entityId}/{accountAddress}/active"), PathParams);

	TArray<FString> QueryParams;
	if(ChainId.IsSet())
	{
		QueryParams.Add(FString(TEXT("chainId=")) + ToUrlString(ChainId.GetValue()));
	}
	Path += TCHAR('?');
	Path += FString::Join(QueryParams, TEXT("&"));

	return Path;
}

void PlayerClientSessionsApi::GetActiveSessionRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("application/json") };

	HttpRequest->SetVerb(TEXT("GET"));

}

void PlayerClientSessionsApi::GetActiveSessionResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);

        if ((int)InHttpResponseCode == 200)
        {
            SetResponseString(TEXT(""));
            return;
        }
        if (GetHttpStatusCategory(InHttpResponseCode) == "4XX")
        {
            SetResponseString(TEXT(""));
            return;
        }
        if (GetHttpStatusCategory(InHttpResponseCode) == "5XX")
        {
            SetResponseString(TEXT(""));
            return;
        }
}

FString PlayerClientSessionsApi::GetActiveSessionResponse::GetHttpStatusCategory(EHttpResponseCodes::Type InHttpResponseCode) {
    int statusCode = (int)InHttpResponseCode;

    // Ensure the input is a valid 3-digit HTTP status code
    if (statusCode < 100 || statusCode > 599) {
        throw std::invalid_argument("Invalid HTTP status code. Must be between 100 and 599.");
    }

    // Extract the first digit and append "XX"
    int firstDigit = statusCode / 100;
    return FString::Printf(TEXT("%dXX"), firstDigit);
}

bool PlayerClientSessionsApi::GetActiveSessionResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

FString PlayerClientSessionsApi::GetActiveSessionV2Request::ComputePath() const
{
	TMap<FString, FStringFormatArg> PathParams = { 
	{ TEXT("entityId"), FStringFormatArg(ToUrlString(EntityId)) },
	{ TEXT("accountAddress"), FStringFormatArg(ToUrlString(AccountAddress)) } };

	FString Path = FString::Format(TEXT("/v2/player/sessions/users/{entityId}/{accountAddress}/active"), PathParams);

	TArray<FString> QueryParams;
	if(ChainId.IsSet())
	{
		QueryParams.Add(FString(TEXT("chainId=")) + ToUrlString(ChainId.GetValue()));
	}
	Path += TCHAR('?');
	Path += FString::Join(QueryParams, TEXT("&"));

	return Path;
}

void PlayerClientSessionsApi::GetActiveSessionV2Request::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("application/json") };

	HttpRequest->SetVerb(TEXT("GET"));

}

void PlayerClientSessionsApi::GetActiveSessionV2Response::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);

        if ((int)InHttpResponseCode == 200)
        {
            SetResponseString(TEXT(""));
            return;
        }
        if (GetHttpStatusCategory(InHttpResponseCode) == "4XX")
        {
            SetResponseString(TEXT(""));
            return;
        }
        if (GetHttpStatusCategory(InHttpResponseCode) == "5XX")
        {
            SetResponseString(TEXT(""));
            return;
        }
}

FString PlayerClientSessionsApi::GetActiveSessionV2Response::GetHttpStatusCategory(EHttpResponseCodes::Type InHttpResponseCode) {
    int statusCode = (int)InHttpResponseCode;

    // Ensure the input is a valid 3-digit HTTP status code
    if (statusCode < 100 || statusCode > 599) {
        throw std::invalid_argument("Invalid HTTP status code. Must be between 100 and 599.");
    }

    // Extract the first digit and append "XX"
    int firstDigit = statusCode / 100;
    return FString::Printf(TEXT("%dXX"), firstDigit);
}

bool PlayerClientSessionsApi::GetActiveSessionV2Response::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

FString PlayerClientSessionsApi::GetAllActiveSessionsRequest::ComputePath() const
{
	TMap<FString, FStringFormatArg> PathParams = { 
	{ TEXT("entityId"), FStringFormatArg(ToUrlString(EntityId)) } };

	FString Path = FString::Format(TEXT("/v1/player/sessions/users/{entityId}/active"), PathParams);

	TArray<FString> QueryParams;
	if(ChainId.IsSet())
	{
		QueryParams.Add(FString(TEXT("chainId=")) + ToUrlString(ChainId.GetValue()));
	}
	Path += TCHAR('?');
	Path += FString::Join(QueryParams, TEXT("&"));

	return Path;
}

void PlayerClientSessionsApi::GetAllActiveSessionsRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("application/json") };

	HttpRequest->SetVerb(TEXT("GET"));

}

void PlayerClientSessionsApi::GetAllActiveSessionsResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);

        if ((int)InHttpResponseCode == 200)
        {
            SetResponseString(TEXT(""));
            return;
        }
        if (GetHttpStatusCategory(InHttpResponseCode) == "4XX")
        {
            SetResponseString(TEXT(""));
            return;
        }
        if (GetHttpStatusCategory(InHttpResponseCode) == "5XX")
        {
            SetResponseString(TEXT(""));
            return;
        }
}

FString PlayerClientSessionsApi::GetAllActiveSessionsResponse::GetHttpStatusCategory(EHttpResponseCodes::Type InHttpResponseCode) {
    int statusCode = (int)InHttpResponseCode;

    // Ensure the input is a valid 3-digit HTTP status code
    if (statusCode < 100 || statusCode > 599) {
        throw std::invalid_argument("Invalid HTTP status code. Must be between 100 and 599.");
    }

    // Extract the first digit and append "XX"
    int firstDigit = statusCode / 100;
    return FString::Printf(TEXT("%dXX"), firstDigit);
}

bool PlayerClientSessionsApi::GetAllActiveSessionsResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

FString PlayerClientSessionsApi::GetSessionRequestRequest::ComputePath() const
{
	TMap<FString, FStringFormatArg> PathParams = { 
	{ TEXT("requestId"), FStringFormatArg(ToUrlString(RequestId)) } };

	FString Path = FString::Format(TEXT("/v1/player/sessions/request/{requestId}"), PathParams);

	return Path;
}

void PlayerClientSessionsApi::GetSessionRequestRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("application/json") };

	HttpRequest->SetVerb(TEXT("GET"));

}

void PlayerClientSessionsApi::GetSessionRequestResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);

        if ((int)InHttpResponseCode == 200)
        {
            SetResponseString(TEXT(""));
            return;
        }
        if (GetHttpStatusCategory(InHttpResponseCode) == "4XX")
        {
            SetResponseString(TEXT(""));
            return;
        }
        if (GetHttpStatusCategory(InHttpResponseCode) == "5XX")
        {
            SetResponseString(TEXT(""));
            return;
        }
}

FString PlayerClientSessionsApi::GetSessionRequestResponse::GetHttpStatusCategory(EHttpResponseCodes::Type InHttpResponseCode) {
    int statusCode = (int)InHttpResponseCode;

    // Ensure the input is a valid 3-digit HTTP status code
    if (statusCode < 100 || statusCode > 599) {
        throw std::invalid_argument("Invalid HTTP status code. Must be between 100 and 599.");
    }

    // Extract the first digit and append "XX"
    int firstDigit = statusCode / 100;
    return FString::Printf(TEXT("%dXX"), firstDigit);
}

bool PlayerClientSessionsApi::GetSessionRequestResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

FString PlayerClientSessionsApi::RevokeSessionRequest::ComputePath() const
{
	TMap<FString, FStringFormatArg> PathParams = { 
	{ TEXT("entityId"), FStringFormatArg(ToUrlString(EntityId)) } };

	FString Path = FString::Format(TEXT("/v1/player/sessions/users/{entityId}/revoke"), PathParams);

	return Path;
}

void PlayerClientSessionsApi::RevokeSessionRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = { TEXT("application/json") };
	//static const TArray<FString> Produces = { TEXT("application/json") };

	HttpRequest->SetVerb(TEXT("POST"));

	// Default to Json Body request
	if (Consumes.Num() == 0 || Consumes.Contains(TEXT("application/json")))
	{
		// Body parameters
		FString JsonBody;
		JsonWriter Writer = TJsonWriterFactory<>::Create(&JsonBody);

		WriteJsonValue(Writer, PlayerClientRevokeSessionRequestInput);
		Writer->Close();

		HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
		HttpRequest->SetContentAsString(JsonBody);
	}
	else if (Consumes.Contains(TEXT("multipart/form-data")))
	{
		UE_LOG(LogPlayerClient, Error, TEXT("Body parameter (PlayerClientRevokeSessionRequestInput) was ignored, not supported in multipart form"));
	}
	else if (Consumes.Contains(TEXT("application/x-www-form-urlencoded")))
	{
		UE_LOG(LogPlayerClient, Error, TEXT("Body parameter (PlayerClientRevokeSessionRequestInput) was ignored, not supported in urlencoded requests"));
	}
	else
	{
		UE_LOG(LogPlayerClient, Error, TEXT("Request ContentType not supported (%s)"), *FString::Join(Consumes, TEXT(",")));
	}
}

void PlayerClientSessionsApi::RevokeSessionResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);

        if ((int)InHttpResponseCode == 200)
        {
            SetResponseString(TEXT(""));
            return;
        }
        if (GetHttpStatusCategory(InHttpResponseCode) == "4XX")
        {
            SetResponseString(TEXT(""));
            return;
        }
        if (GetHttpStatusCategory(InHttpResponseCode) == "5XX")
        {
            SetResponseString(TEXT(""));
            return;
        }
}

FString PlayerClientSessionsApi::RevokeSessionResponse::GetHttpStatusCategory(EHttpResponseCodes::Type InHttpResponseCode) {
    int statusCode = (int)InHttpResponseCode;

    // Ensure the input is a valid 3-digit HTTP status code
    if (statusCode < 100 || statusCode > 599) {
        throw std::invalid_argument("Invalid HTTP status code. Must be between 100 and 599.");
    }

    // Extract the first digit and append "XX"
    int firstDigit = statusCode / 100;
    return FString::Printf(TEXT("%dXX"), firstDigit);
}

bool PlayerClientSessionsApi::RevokeSessionResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

}
