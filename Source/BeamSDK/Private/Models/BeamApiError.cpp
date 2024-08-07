#include "BeamApiError.h"

DEFINE_LOG_CATEGORY_STATIC(LogBeamApiError, Log, All);

bool FBeamApiError::FromJson(const FString& InJsonString, FBeamApiError& OutBeamApiError)
{
	if (FBeamUtils::JsonToStruct(InJsonString, OutBeamApiError))
	{
		return true;
	}
	return false;
}


bool FBeamApiError::FromJson(const FString& InJsonString)
{
	return FromJson(InJsonString, *this);
}


//
// --- TESTS ---
//

void FBeamApiError::Test(const FString& TestName, const FString& TestJson)
{
	UE_LOG(LogBeamApiError, Log, TEXT("----- %s - TESTING... -----."), *TestName);
	FBeamApiError testApiError;
	if (testApiError.FromJson(TestJson))
	{
		if (testApiError.Status == 123)
		{
			UE_LOG(LogBeamApiError, Log, TEXT("----- %s - PASS -----."), *TestName);
		}
		else
		{
			UE_LOG(LogBeamApiError, Error, TEXT("----- %s - FAIL -----"), *TestName);
		}
		UE_LOG(LogBeamApiError, Log,
			TEXT(
				"* From Json : %s\n"
				"- Timestamp : %s\n"
				"- Status    : %d\n"
				"- Error     : %s\n"
				"- Type      : %s\n"
				"- Message   : %s\n"
				"- Path      : %s\n"
				"- TraceId   : %s\n"
			),
			*TestJson,
			*testApiError.Timestamp,
			testApiError.Status,
			*testApiError.Error,
			*testApiError.Type,
			*testApiError.Message,
			*testApiError.Path,
			*testApiError.TraceId
		);
	}
	else
	{
		UE_LOG(LogBeamApiError, Error, TEXT("----- %s - PARSE FAILED -----"), *TestName);
	}
}

void FBeamApiError::Test_Basic()
{
	const FString testJson = TEXT(
		"{"
		"\"Timestamp\":\"12:00:00\","
		"\"Status\":123,"
		"\"Error\":\"err\","
		"\"Type\":\"abc\","
		"\"Message\":\"xyz\","
		"\"Path\":\"/path/\","
		"\"TraceId\":\"id:123\""
		"}"
	);
	const FString testName = FString::Printf(TEXT("%hs"), __FUNCTION__);
	Test(testName, testJson);
}

