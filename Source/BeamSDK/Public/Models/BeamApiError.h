#pragma once

#include "BeamUtils.h"

#include "BeamApiError.generated.h"

USTRUCT()
struct FBeamApiError
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString Timestamp;

	UPROPERTY()
	int32 Status = 0;

	UPROPERTY()
	FString Error;

	UPROPERTY()
	FString Type;

	UPROPERTY()
	FString Message;

	UPROPERTY()
	FString Path;

	UPROPERTY()
	FString TraceId;

public:
	static bool FromJson(const FString& InJsonString, FBeamApiError& OutBeamApiError);

	bool FromJson(const FString& InJsonString);

public:
	static void Test(const FString& TestName, const FString& TestJson);
	static void Test_Basic();
};
