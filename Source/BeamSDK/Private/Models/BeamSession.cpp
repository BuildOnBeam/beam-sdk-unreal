#include "BeamSession.h"
#include "BeamUtils.h"
#include "BeamPlayerClientAPI.h"

DEFINE_LOG_CATEGORY_STATIC(LogBeamSession, Log, All);

FBeamSession::FBeamSession() {}

FBeamSession::FBeamSession(FString& InJsonString)
{
	FromJson(InJsonString, *this);
}

FBeamSession::FBeamSession(PlayerClientSessionsApi::GetActiveSessionResponse& ApiResponse)
{
	Id = ApiResponse.Content.Id;
	SessionAddress = ApiResponse.Content.SessionAddress;
	StartTime = ApiResponse.Content.StartTime;
	EndTime = ApiResponse.Content.EndTime;
}

FBeamSession::FBeamSession(PlayerClientSessionsApi::GetActiveSessionV2Response& ApiV2Response)
{
	Id = ApiV2Response.Content.Session.GetValue().Id;
	SessionAddress = ApiV2Response.Content.Session.GetValue().SessionAddress;
	StartTime = ApiV2Response.Content.Session.GetValue().StartTime;
	EndTime = ApiV2Response.Content.Session.GetValue().EndTime;
}

bool FBeamSession::FromJson(const FString& InJsonString, FBeamSession& OutBeamSession)
{
	TSharedPtr<FJsonObject> JsonObject;
	if (FBeamUtils::DeserializeJson(InJsonString, JsonObject))
	{
		OutBeamSession.Id = JsonObject->GetStringField(TEXT("id"));
		OutBeamSession.SessionAddress = JsonObject->GetStringField(TEXT("sessionAddress"));
		ParseDateTime(JsonObject->GetStringField(TEXT("startTime")), OutBeamSession.StartTime);
		ParseDateTime(JsonObject->GetStringField(TEXT("endTime")), OutBeamSession.EndTime);
		return true;
	}
	return false;
}

bool FBeamSession::FromJson(const FString& InJsonString)
{
	return FromJson(InJsonString, *this);
}

FString FBeamSession::WriteJson()
{
	FString jsonString = FString::Printf(TEXT(
R"({
  "id":"%s",
  "sessionAddress":"%s",
  "startTime":"%s",
  "endTime":"%s"
})"),
		*Id,
		*SessionAddress,
		*StartTime.ToIso8601(),
		*EndTime.ToIso8601());
	return jsonString;
}

bool FBeamSession::IsValidNow()
{
	auto now = FDateTime::UtcNow();
	return StartTime <= now && EndTime > now;
}

bool FBeamSession::IsOwnedBy(KeyPair keyPair)
{
	return SessionAddress.Equals(keyPair.GetAddress().c_str(), ESearchCase::IgnoreCase);
}
