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
#include "PlayerClientMarketplaceApi.h"

#include "PlayerClientAcceptAssetOfferRequestInput.h"
#include "PlayerClientBuyAssetRequestInput.h"
#include "PlayerClientCancelAssetListingRequestInput.h"
#include "PlayerClientCancelAssetOfferRequestInput.h"
#include "PlayerClientCreateAssetOfferRequestInput.h"
#include "PlayerClientGetAssetListingsResponse.h"
#include "PlayerClientGetChainCurrenciesResponse.h"
#include "PlayerClientGetListedAssetsBodyInput.h"
#include "PlayerClientPlayerOperationResponse.h"
#include "PlayerClientRefreshContractRequestBody.h"
#include "PlayerClientRefreshTokenRequestBody.h"
#include "PlayerClientSellAssetRequestInput.h"

namespace OpenAPI
{

/* Accept an offer for an asset

*/
class PLAYERCLIENT_API PlayerClientMarketplaceApi::AcceptAssetOfferRequest : public Request
{
public:
    virtual ~AcceptAssetOfferRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString EntityId;
	FString OfferId;
	PlayerClientAcceptAssetOfferRequestInput PlayerClientAcceptAssetOfferRequestInput;
};

class PLAYERCLIENT_API PlayerClientMarketplaceApi::AcceptAssetOfferResponse : public Response
{
public:
    virtual ~AcceptAssetOfferResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientPlayerOperationResponse Content;
};

/* Buy listed asset

*/
class PLAYERCLIENT_API PlayerClientMarketplaceApi::BuyListedAssetRequest : public Request
{
public:
    virtual ~BuyListedAssetRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString EntityId;
	FString OrderId;
	PlayerClientBuyAssetRequestInput PlayerClientBuyAssetRequestInput;
};

class PLAYERCLIENT_API PlayerClientMarketplaceApi::BuyListedAssetResponse : public Response
{
public:
    virtual ~BuyListedAssetResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientPlayerOperationResponse Content;
};

/* Cancel an offer for an asset

*/
class PLAYERCLIENT_API PlayerClientMarketplaceApi::CancelAssetOfferRequest : public Request
{
public:
    virtual ~CancelAssetOfferRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString EntityId;
	FString OfferId;
	PlayerClientCancelAssetOfferRequestInput PlayerClientCancelAssetOfferRequestInput;
};

class PLAYERCLIENT_API PlayerClientMarketplaceApi::CancelAssetOfferResponse : public Response
{
public:
    virtual ~CancelAssetOfferResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientPlayerOperationResponse Content;
};

/* Cancel asset listing

*/
class PLAYERCLIENT_API PlayerClientMarketplaceApi::CancelListingRequest : public Request
{
public:
    virtual ~CancelListingRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString EntityId;
	FString OrderId;
	PlayerClientCancelAssetListingRequestInput PlayerClientCancelAssetListingRequestInput;
	TOptional<int64> ChainId;
};

class PLAYERCLIENT_API PlayerClientMarketplaceApi::CancelListingResponse : public Response
{
public:
    virtual ~CancelListingResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientPlayerOperationResponse Content;
};

/* Make an offer for an asset

*/
class PLAYERCLIENT_API PlayerClientMarketplaceApi::CreateAssetOfferRequest : public Request
{
public:
    virtual ~CreateAssetOfferRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString EntityId;
	PlayerClientCreateAssetOfferRequestInput PlayerClientCreateAssetOfferRequestInput;
};

class PLAYERCLIENT_API PlayerClientMarketplaceApi::CreateAssetOfferResponse : public Response
{
public:
    virtual ~CreateAssetOfferResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientPlayerOperationResponse Content;
};

/* Get all offers for an asset

*/
class PLAYERCLIENT_API PlayerClientMarketplaceApi::GetAssetOffersRequest : public Request
{
public:
    virtual ~GetAssetOffersRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString AssetAddress;
	FString AssetId;
	TOptional<int64> ChainId;
	TOptional<FString> Continuation;
};

class PLAYERCLIENT_API PlayerClientMarketplaceApi::GetAssetOffersResponse : public Response
{
public:
    virtual ~GetAssetOffersResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientGetAssetListingsResponse Content;
};

/* Get available currencies for given chain

*/
class PLAYERCLIENT_API PlayerClientMarketplaceApi::GetChainCurrenciesRequest : public Request
{
public:
    virtual ~GetChainCurrenciesRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	int64 ChainId = 0;
};

class PLAYERCLIENT_API PlayerClientMarketplaceApi::GetChainCurrenciesResponse : public Response
{
public:
    virtual ~GetChainCurrenciesResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientGetChainCurrenciesResponse Content;
};

/* Get all listed assets for a game (NFT assets, e.g. ERC721 / ERC1155)

*/
class PLAYERCLIENT_API PlayerClientMarketplaceApi::GetListedAssetsRequest : public Request
{
public:
    virtual ~GetListedAssetsRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	PlayerClientGetListedAssetsBodyInput PlayerClientGetListedAssetsBodyInput;
};

class PLAYERCLIENT_API PlayerClientMarketplaceApi::GetListedAssetsResponse : public Response
{
public:
    virtual ~GetListedAssetsResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientGetAssetListingsResponse Content;
};

/* Get all the assets listed by a profile (NFT assets, e.g. ERC721 / ERC1155)

*/
class PLAYERCLIENT_API PlayerClientMarketplaceApi::GetListedAssetsForUserRequest : public Request
{
public:
    virtual ~GetListedAssetsForUserRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString EntityId;
	PlayerClientGetListedAssetsBodyInput PlayerClientGetListedAssetsBodyInput;
};

class PLAYERCLIENT_API PlayerClientMarketplaceApi::GetListedAssetsForUserResponse : public Response
{
public:
    virtual ~GetListedAssetsForUserResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientGetAssetListingsResponse Content;
};

/* Get all asset offers that a user created for a specific asset

*/
class PLAYERCLIENT_API PlayerClientMarketplaceApi::GetUserAssetOffersRequest : public Request
{
public:
    virtual ~GetUserAssetOffersRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString EntityId;
	FString AssetAddress;
	FString AssetId;
	TOptional<int64> ChainId;
	TOptional<FString> Continuation;
};

class PLAYERCLIENT_API PlayerClientMarketplaceApi::GetUserAssetOffersResponse : public Response
{
public:
    virtual ~GetUserAssetOffersResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientGetAssetListingsResponse Content;
};

/* Get all offers that a user created

*/
class PLAYERCLIENT_API PlayerClientMarketplaceApi::GetUserOffersRequest : public Request
{
public:
    virtual ~GetUserOffersRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString EntityId;
	TOptional<int64> ChainId;
	TOptional<FString> Continuation;
};

class PLAYERCLIENT_API PlayerClientMarketplaceApi::GetUserOffersResponse : public Response
{
public:
    virtual ~GetUserOffersResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientGetAssetListingsResponse Content;
};

/* List an asset for sale

*/
class PLAYERCLIENT_API PlayerClientMarketplaceApi::ListAssetRequest : public Request
{
public:
    virtual ~ListAssetRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString EntityId;
	PlayerClientSellAssetRequestInput PlayerClientSellAssetRequestInput;
};

class PLAYERCLIENT_API PlayerClientMarketplaceApi::ListAssetResponse : public Response
{
public:
    virtual ~ListAssetResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientPlayerOperationResponse Content;
};

/* Schedule a contract refresh in the indexer

*/
class PLAYERCLIENT_API PlayerClientMarketplaceApi::RefreshContractRequest : public Request
{
public:
    virtual ~RefreshContractRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	PlayerClientRefreshContractRequestBody PlayerClientRefreshContractRequestBody;
};

class PLAYERCLIENT_API PlayerClientMarketplaceApi::RefreshContractResponse : public Response
{
public:
    virtual ~RefreshContractResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    
};

/* Schedule a token refresh in the indexer

*/
class PLAYERCLIENT_API PlayerClientMarketplaceApi::RefreshTokenRequest : public Request
{
public:
    virtual ~RefreshTokenRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	PlayerClientRefreshTokenRequestBody PlayerClientRefreshTokenRequestBody;
};

class PLAYERCLIENT_API PlayerClientMarketplaceApi::RefreshTokenResponse : public Response
{
public:
    virtual ~RefreshTokenResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    
};

}
