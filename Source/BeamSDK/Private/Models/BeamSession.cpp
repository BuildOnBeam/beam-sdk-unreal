#include "BeamSession.h"

#include "BeamUtils.h"

#include "BeamPlayerClientAPI.h"

#include "PlayerClientHelpers.h"
using OpenAPI::ParseDateTime;

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
		"{"
		"\"id\": \"%s\","
		"\"sessionAddress\": \"%s\","
		"\"startTime\": \"%s\","
		"\"endTime\": \"%s\""
		"}"),
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

void FBeamSession::Test_ReadWrite()
{
	FDateTime StartTime = FDateTime::UtcNow();
	FDateTime EndTime = FDateTime::UtcNow() + FTimespan(0, 5, 0);

	FBeamSession TestSession;
	TestSession.Id =TEXT("clTEST000000000000000TEST");
	TestSession.SessionAddress = TEXT("0xTEST00000000000000000000000000000000TEST");
	TestSession.StartTime = StartTime;
	TestSession.EndTime = EndTime;
	FString TestJson = TestSession.WriteJson();
	UE_LOG(LogBeamSession, Log, TEXT("TestJson: %s"), *TestJson);

	FBeamSession TestSession2;
	TestSession2.FromJson(TestJson);
	UE_LOG(LogBeamSession, Log, TEXT("EndTime: %s"), *TestSession2.EndTime.ToIso8601());

	if (TestSession2.EndTime == TestSession.EndTime)
	{
		UE_LOG(LogBeamSession, Log, TEXT("----- ReadWrite - PASS -----."));
	}
	else
	{
		UE_LOG(LogBeamSession, Log, TEXT("----- ReadWrite - FAIL -----."));
	}
}
