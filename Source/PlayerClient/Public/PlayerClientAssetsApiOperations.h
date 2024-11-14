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
#include "PlayerClientAssetsApi.h"

#include "PlayerClientGetAssetResponse.h"
#include "PlayerClientGetAssetsForContractBodyInput.h"
#include "PlayerClientGetAssetsForContractResponse.h"
#include "PlayerClientGetAssetsForUserBodyInput.h"
#include "PlayerClientGetAssetsForUserResponse.h"
#include "PlayerClientGetAttributesResponse.h"
#include "PlayerClientGetOwnerAssetsBodyInput.h"
#include "PlayerClientGetOwnerAssetsResponse.h"
#include "PlayerClientGetOwnersResponse.h"
#include "PlayerClientGetUserCurrenciesResponse.h"
#include "PlayerClientGetUserNativeCurrencyResponse.h"
#include "PlayerClientPlayerOperationResponse.h"
#include "PlayerClientTransferAssetRequestInput.h"
#include "PlayerClientTransferNativeTokenRequestInput.h"
#include "PlayerClientTransferTokenRequestInput.h"

namespace OpenAPI
{

/* Get a single NFT (e.g. ERC721 / ERC1155)

*/
class PLAYERCLIENT_API PlayerClientAssetsApi::GetAssetRequest : public Request
{
public:
    virtual ~GetAssetRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString AssetAddress;
	FString AssetId;
	TOptional<int64> ChainId;
	/* If true, will always return 'owners' record for this User if he owns the asset */
	TOptional<FString> EntityId;
	/* If true, will return all owners of the asset */
	TOptional<bool> Owners;
};

class PLAYERCLIENT_API PlayerClientAssetsApi::GetAssetResponse : public Response
{
public:
    virtual ~GetAssetResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientGetAssetResponse Content;
};

/* Get all the assets of contract (NFT assets, e.g. ERC721 / ERC1155)

*/
class PLAYERCLIENT_API PlayerClientAssetsApi::GetAssetsForContractRequest : public Request
{
public:
    virtual ~GetAssetsForContractRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString AssetAddress;
	PlayerClientGetAssetsForContractBodyInput PlayerClientGetAssetsForContractBodyInput;
};

class PLAYERCLIENT_API PlayerClientAssetsApi::GetAssetsForContractResponse : public Response
{
public:
    virtual ~GetAssetsForContractResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientGetAssetsForContractResponse Content;
};

/* 

*/
class PLAYERCLIENT_API PlayerClientAssetsApi::GetAttributesRequest : public Request
{
public:
    virtual ~GetAttributesRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString AssetAddress;
	int64 ChainId = 0;
};

class PLAYERCLIENT_API PlayerClientAssetsApi::GetAttributesResponse : public Response
{
public:
    virtual ~GetAttributesResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientGetAttributesResponse Content;
};

/* 

*/
class PLAYERCLIENT_API PlayerClientAssetsApi::GetOwnerAssetsRequest : public Request
{
public:
    virtual ~GetOwnerAssetsRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString AssetAddress;
	FString OwnerAddress;
	PlayerClientGetOwnerAssetsBodyInput PlayerClientGetOwnerAssetsBodyInput;
};

class PLAYERCLIENT_API PlayerClientAssetsApi::GetOwnerAssetsResponse : public Response
{
public:
    virtual ~GetOwnerAssetsResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientGetOwnerAssetsResponse Content;
};

/* 

*/
class PLAYERCLIENT_API PlayerClientAssetsApi::GetOwnersRequest : public Request
{
public:
    virtual ~GetOwnersRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString AssetAddress;
	int64 ChainId = 0;
	TOptional<double> Limit;
	TOptional<double> Offset;
};

class PLAYERCLIENT_API PlayerClientAssetsApi::GetOwnersResponse : public Response
{
public:
    virtual ~GetOwnersResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientGetOwnersResponse Content;
};

/* Get all the assets of a profile (NFT assets, e.g. ERC721 / ERC1155)

*/
class PLAYERCLIENT_API PlayerClientAssetsApi::GetUserAssetsForGamePostRequest : public Request
{
public:
    virtual ~GetUserAssetsForGamePostRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString EntityId;
	PlayerClientGetAssetsForUserBodyInput PlayerClientGetAssetsForUserBodyInput;
};

class PLAYERCLIENT_API PlayerClientAssetsApi::GetUserAssetsForGamePostResponse : public Response
{
public:
    virtual ~GetUserAssetsForGamePostResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientGetAssetsForUserResponse Content;
};

/* Get all the currencies owned by an account (ERC20)

*/
class PLAYERCLIENT_API PlayerClientAssetsApi::GetUserCurrenciesRequest : public Request
{
public:
    virtual ~GetUserCurrenciesRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString EntityId;
	TOptional<int64> ChainId;
};

class PLAYERCLIENT_API PlayerClientAssetsApi::GetUserCurrenciesResponse : public Response
{
public:
    virtual ~GetUserCurrenciesResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientGetUserCurrenciesResponse Content;
};

/* Get the native token balance

*/
class PLAYERCLIENT_API PlayerClientAssetsApi::GetUserNativeCurrencyRequest : public Request
{
public:
    virtual ~GetUserNativeCurrencyRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString EntityId;
	TOptional<int64> ChainId;
};

class PLAYERCLIENT_API PlayerClientAssetsApi::GetUserNativeCurrencyResponse : public Response
{
public:
    virtual ~GetUserNativeCurrencyResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientGetUserNativeCurrencyResponse Content;
};

/* Transfer an asset (NFT assets, ERC721 / ERC1155)

*/
class PLAYERCLIENT_API PlayerClientAssetsApi::TransferAssetRequest : public Request
{
public:
    virtual ~TransferAssetRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString EntityId;
	PlayerClientTransferAssetRequestInput PlayerClientTransferAssetRequestInput;
};

class PLAYERCLIENT_API PlayerClientAssetsApi::TransferAssetResponse : public Response
{
public:
    virtual ~TransferAssetResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientPlayerOperationResponse Content;
};

/* Transfer the native token

*/
class PLAYERCLIENT_API PlayerClientAssetsApi::TransferNativeTokenRequest : public Request
{
public:
    virtual ~TransferNativeTokenRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString EntityId;
	PlayerClientTransferNativeTokenRequestInput PlayerClientTransferNativeTokenRequestInput;
};

class PLAYERCLIENT_API PlayerClientAssetsApi::TransferNativeTokenResponse : public Response
{
public:
    virtual ~TransferNativeTokenResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientPlayerOperationResponse Content;
};

/* Transfer a token (token assets, ERC20)

*/
class PLAYERCLIENT_API PlayerClientAssetsApi::TransferTokenRequest : public Request
{
public:
    virtual ~TransferTokenRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString EntityId;
	PlayerClientTransferTokenRequestInput PlayerClientTransferTokenRequestInput;
};

class PLAYERCLIENT_API PlayerClientAssetsApi::TransferTokenResponse : public Response
{
public:
    virtual ~TransferTokenResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientPlayerOperationResponse Content;
};

}
