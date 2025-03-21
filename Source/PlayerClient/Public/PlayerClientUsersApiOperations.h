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
#include "PlayerClientUsersApi.h"
#include <string>
#include <stdexcept>
    
#include "PlayerClientBeamErrorResponse.h"
#include "PlayerClientGetAllUsersResponse.h"
#include "PlayerClientGetUserResponse.h"
#include "PlayerClientUpdateUserRequest.h"

namespace OpenAPI
{

/* Returns a list of users

*/
class PLAYERCLIENT_API PlayerClientUsersApi::GetAllUsersRequest : public Request
{
public:
    virtual ~GetAllUsersRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	TOptional<double> Limit;
	TOptional<double> Offset;
};

class PLAYERCLIENT_API PlayerClientUsersApi::GetAllUsersResponse : public Response
{
public:
    virtual ~GetAllUsersResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientGetAllUsersResponse Content;
private:
    FString GetHttpStatusCategory(EHttpResponseCodes::Type InHttpResponseCode);
};

/* Returns a particular user

*/
class PLAYERCLIENT_API PlayerClientUsersApi::GetUserRequest : public Request
{
public:
    virtual ~GetUserRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString EntityId;
};

class PLAYERCLIENT_API PlayerClientUsersApi::GetUserResponse : public Response
{
public:
    virtual ~GetUserResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientGetUserResponse Content;
private:
    FString GetHttpStatusCategory(EHttpResponseCodes::Type InHttpResponseCode);
};

/* Unlinks an entity ID from a user

*/
class PLAYERCLIENT_API PlayerClientUsersApi::UnlinkUserRequest : public Request
{
public:
    virtual ~UnlinkUserRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString EntityId;
};

class PLAYERCLIENT_API PlayerClientUsersApi::UnlinkUserResponse : public Response
{
public:
    virtual ~UnlinkUserResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientGetUserResponse Content;
private:
    FString GetHttpStatusCategory(EHttpResponseCodes::Type InHttpResponseCode);
};

/* Updates entityId for the user

*/
class PLAYERCLIENT_API PlayerClientUsersApi::UpdateUserRequest : public Request
{
public:
    virtual ~UpdateUserRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString EntityId;
	PlayerClientUpdateUserRequest PlayerClientUpdateUserRequest;
};

class PLAYERCLIENT_API PlayerClientUsersApi::UpdateUserResponse : public Response
{
public:
    virtual ~UpdateUserResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    PlayerClientGetUserResponse Content;
private:
    FString GetHttpStatusCategory(EHttpResponseCodes::Type InHttpResponseCode);
};

}
