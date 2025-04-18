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

#include "PlayerClientGetActiveSessionResponseV2Session.h"

#include "PlayerClientModule.h"
#include "PlayerClientHelpers.h"

#include "Templates/SharedPointer.h"

namespace OpenAPI
{

void PlayerClientGetActiveSessionResponseV2Session::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	Writer->WriteIdentifierPrefix(TEXT("id")); WriteJsonValue(Writer, Id);
	Writer->WriteIdentifierPrefix(TEXT("isActive")); WriteJsonValue(Writer, IsActive);
	Writer->WriteIdentifierPrefix(TEXT("startTime")); WriteJsonValue(Writer, StartTime);
	Writer->WriteIdentifierPrefix(TEXT("endTime")); WriteJsonValue(Writer, EndTime);
	Writer->WriteIdentifierPrefix(TEXT("sessionAddress")); WriteJsonValue(Writer, SessionAddress);
	Writer->WriteObjectEnd();
}

bool PlayerClientGetActiveSessionResponseV2Session::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("id"), Id);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("isActive"), IsActive);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("startTime"), StartTime);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("endTime"), EndTime);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("sessionAddress"), SessionAddress);

	return ParseSuccess;
}

}
