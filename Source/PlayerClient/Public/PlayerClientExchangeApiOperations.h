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
#include "PlayerClientExchangeApi.h"
#include <string>
#include <stdexcept>
    
#include "PlayerClientBeamErrorResponse.h"
#include "PlayerClientConvertTokenRequestInput.h"
#include "PlayerClientGetQuoteResponse.h"
#include "PlayerClientPlayerOperationResponse.h"
#include "PlayerClientUnwrappingTokenInput.h"
#include "PlayerClientWrappingTokenInput.h"

namespace OpenAPI
{

/* Swap an exact amount of &#x60;tokenIn&#x60; for a minimum amount of &#x60;tokenOut&#x60;

*/
class PLAYERCLIENT_API PlayerClientExchangeApi::ConvertInputRequest : public Request
{
public:
    virtual ~ConvertInputRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString EntityId;
	PlayerClientConvertTokenRequestInput PlayerClientConvertTokenRequestInput;
};

class PLAYERCLIENT_API PlayerClientExchangeApi::ConvertInputResponse : public Response
{
public:
    virtual ~ConvertInputResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientPlayerOperationResponse Content;
private:
    std::string GetHttpStatusCategory(EHttpResponseCodes::Type InHttpResponseCode);
};

/* Swap a maximum amount of &#x60;tokenIn&#x60; for an exact amount of &#x60;tokenOut&#x60;

*/
class PLAYERCLIENT_API PlayerClientExchangeApi::ConvertToOutputRequest : public Request
{
public:
    virtual ~ConvertToOutputRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString EntityId;
	PlayerClientConvertTokenRequestInput PlayerClientConvertTokenRequestInput;
};

class PLAYERCLIENT_API PlayerClientExchangeApi::ConvertToOutputResponse : public Response
{
public:
    virtual ~ConvertToOutputResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientPlayerOperationResponse Content;
private:
    std::string GetHttpStatusCategory(EHttpResponseCodes::Type InHttpResponseCode);
};

/* Returns the maximum necessary input amount for a token trade, given a desired output amount

*/
class PLAYERCLIENT_API PlayerClientExchangeApi::GetQuoteForInputRequest : public Request
{
public:
    virtual ~GetQuoteForInputRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString TokenIn;
	FString TokenOut;
	FString AmountOut;
	TOptional<int64> ChainId;
};

class PLAYERCLIENT_API PlayerClientExchangeApi::GetQuoteForInputResponse : public Response
{
public:
    virtual ~GetQuoteForInputResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientGetQuoteResponse Content;
private:
    std::string GetHttpStatusCategory(EHttpResponseCodes::Type InHttpResponseCode);
};

/* Returns the minimum expected output amount for a token trade, given an input amount

*/
class PLAYERCLIENT_API PlayerClientExchangeApi::GetQuoteForOutputRequest : public Request
{
public:
    virtual ~GetQuoteForOutputRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString TokenIn;
	FString TokenOut;
	FString AmountIn;
	TOptional<int64> ChainId;
};

class PLAYERCLIENT_API PlayerClientExchangeApi::GetQuoteForOutputResponse : public Response
{
public:
    virtual ~GetQuoteForOutputResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientGetQuoteResponse Content;
private:
    std::string GetHttpStatusCategory(EHttpResponseCodes::Type InHttpResponseCode);
};

/* Unwrap an amount of wrapped to native token

*/
class PLAYERCLIENT_API PlayerClientExchangeApi::UnwrapNativeRequest : public Request
{
public:
    virtual ~UnwrapNativeRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString EntityId;
	PlayerClientUnwrappingTokenInput PlayerClientUnwrappingTokenInput;
};

class PLAYERCLIENT_API PlayerClientExchangeApi::UnwrapNativeResponse : public Response
{
public:
    virtual ~UnwrapNativeResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientPlayerOperationResponse Content;
private:
    std::string GetHttpStatusCategory(EHttpResponseCodes::Type InHttpResponseCode);
};

/* Wrap an amount of native token to wrapped native token

*/
class PLAYERCLIENT_API PlayerClientExchangeApi::WrapNativeRequest : public Request
{
public:
    virtual ~WrapNativeRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString EntityId;
	PlayerClientWrappingTokenInput PlayerClientWrappingTokenInput;
};

class PLAYERCLIENT_API PlayerClientExchangeApi::WrapNativeResponse : public Response
{
public:
    virtual ~WrapNativeResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientPlayerOperationResponse Content;
private:
    std::string GetHttpStatusCategory(EHttpResponseCodes::Type InHttpResponseCode);
};

}
