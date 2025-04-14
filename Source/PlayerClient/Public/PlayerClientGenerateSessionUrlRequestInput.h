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

namespace OpenAPI
{

/*
 * PlayerClientGenerateSessionUrlRequestInput
 *
 * 
 */
class PLAYERCLIENT_API PlayerClientGenerateSessionUrlRequestInput : public Model
{
public:
    virtual ~PlayerClientGenerateSessionUrlRequestInput() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	FString Address;
	TOptional<FString> EntityId;
	TOptional<FDateTime> SuggestedExpiry;
	enum class AuthProviderEnum
	{
		Any,
		Google,
		Discord,
		Apple,
  	};

	static FString EnumToString(const AuthProviderEnum& EnumValue);
	static bool EnumFromString(const FString& EnumAsString, AuthProviderEnum& EnumValue);
	/* Auth Provider for the user to use. If it's Any, user will be able to choose his preferred login method. Useful when you want to present social login choice in your UI. */
	TOptional<AuthProviderEnum> AuthProvider;
	/* List of contract addresses to be used in the session */
	TOptional<TArray<FString>> Contracts;
	TOptional<int64> ChainId;
};

}
