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
 * PlayerClientPlayerOperationResponseTransactionsInner
 *
 * 
 */
class PLAYERCLIENT_API PlayerClientPlayerOperationResponseTransactionsInner : public Model
{
public:
    virtual ~PlayerClientPlayerOperationResponseTransactionsInner() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	enum class StatusEnum
	{
		Pending,
		_Signed,
		Rejected,
		Executed,
		Error,
  	};

	static FString EnumToString(const StatusEnum& EnumValue);
	static bool EnumFromString(const FString& EnumAsString, StatusEnum& EnumValue);
	StatusEnum Status;
	FString Id;
	TOptional<FString> OpenfortId;
	bool Sponsored = false;
	TOptional<FString> ActionId;
	FString Hash;
	enum class TypeEnum
	{
		OpenfortTransaction,
		OpenfortReservoirOrder,
		OpenfortRevokeSession,
  	};

	static FString EnumToString(const TypeEnum& EnumValue);
	static bool EnumFromString(const FString& EnumAsString, TypeEnum& EnumValue);
	TOptional<TypeEnum> Type;
	TOptional<FString> ExternalId;
	TOptional<FString> Signature;
	TOptional<FString> TransactionHash;
	TOptional<FString> OperationId;
	TOptional<TSharedPtr<FJsonValue>> Data;
};

}