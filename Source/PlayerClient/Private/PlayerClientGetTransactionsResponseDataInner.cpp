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

#include "PlayerClientGetTransactionsResponseDataInner.h"

#include "PlayerClientModule.h"
#include "PlayerClientHelpers.h"

#include "Templates/SharedPointer.h"

namespace OpenAPI
{

void PlayerClientGetTransactionsResponseDataInner::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	Writer->WriteIdentifierPrefix(TEXT("id")); WriteJsonValue(Writer, Id);
	Writer->WriteIdentifierPrefix(TEXT("createdAt")); WriteJsonValue(Writer, CreatedAt);
	Writer->WriteIdentifierPrefix(TEXT("updatedAt")); WriteJsonValue(Writer, UpdatedAt);
	Writer->WriteIdentifierPrefix(TEXT("chainId")); WriteJsonValue(Writer, ChainId);
	Writer->WriteIdentifierPrefix(TEXT("intent")); WriteJsonValue(Writer, Intent);
	if (Transaction.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("transaction")); WriteJsonValue(Writer, Transaction.GetValue());
	}
	Writer->WriteObjectEnd();
}

bool PlayerClientGetTransactionsResponseDataInner::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("id"), Id);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("createdAt"), CreatedAt);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("updatedAt"), UpdatedAt);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("chainId"), ChainId);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("intent"), Intent);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("transaction"), Transaction);

	return ParseSuccess;
}

}