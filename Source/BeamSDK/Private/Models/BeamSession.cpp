#include "BeamSession.h"

#include "BeamUtils.h"

#include "PlayerClientHelpers.h"
using OpenAPI::ParseDateTime;

DEFINE_LOG_CATEGORY_STATIC(LogBeamSession, Log, All);

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


//
// --- TESTS ---
//

void FBeamSession::Test(const FString& TestName, const FString& TestJson)
{
	UE_LOG(LogBeamSession, Log, TEXT("----- %s - TESTING... -----."), *TestName);
	FBeamSession testBeamSession;
	if (testBeamSession.FromJson(TestJson))
	{
		if (testBeamSession.Id.Compare(TEXT("123")) == 0)
		{
			UE_LOG(LogBeamSession, Log, TEXT("----- %s - PASS -----."), *TestName);
		}
		else
		{
			UE_LOG(LogBeamSession, Error, TEXT("----- %s - FAIL -----"), *TestName);
		}
		UE_LOG(LogBeamSession, Log,
			TEXT(
				"* From Json : %s\n"
				"- Id             : %s\n"
				"- SessionAddress : %s\n"
				"- StartTime      : %s\n"
				"- EndTime        : %s\n"
			),
			*TestJson,
			*testBeamSession.Id,
			*testBeamSession.SessionAddress,
			*testBeamSession.StartTime.ToString(),
			*testBeamSession.EndTime.ToString()
		);
	}
	else
	{
		UE_LOG(LogBeamSession, Error, TEXT("----- %s - PARSE FAILED -----"), *TestName);
	}
}

void FBeamSession::Test_Basic()
{
	const FString testJson = TEXT(
		"{"
		"\"Id\":\"123\","
		"\"SessionAddress\":\"xyz\","
		"\"StartTime\":\"2024-08-02T12:34:56Z\","
		"\"EndTime\":\"2024-08-02T12:34:56Z\""
		"}"
	);
	const FString testName = FString::Printf(TEXT("%hs"), __FUNCTION__);
	Test(testName, testJson);
}
