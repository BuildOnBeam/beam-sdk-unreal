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
 * PlayerClientUnwrappingTokenInput
 *
 * 
 */
class PLAYERCLIENT_API PlayerClientUnwrappingTokenInput : public Model
{
public:
    virtual ~PlayerClientUnwrappingTokenInput() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	FString Amount;
	TOptional<bool> Optimistic;
	TOptional<bool> Sponsor;
	TOptional<FString> PolicyId;
	TOptional<int64> ChainId;
	enum class OperationProcessingEnum
	{
		SignOnly,
		Execute,
  	};

	static FString EnumToString(const OperationProcessingEnum& EnumValue);
	static bool EnumFromString(const FString& EnumAsString, OperationProcessingEnum& EnumValue);
	/* Operation processing type. If Execute is used, Operation will be executed automatically right after User signs it. If you prefer to have more control, use SignOnly then Process it using ProcessOperation. */
	TOptional<OperationProcessingEnum> OperationProcessing;
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
};

}
