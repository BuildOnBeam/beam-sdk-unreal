#pragma once

#include "Misc/DateTime.h"

#include "BeamSession.generated.h"

USTRUCT()
struct FBeamSession
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString Id;

	UPROPERTY()
	FString SessionAddress;

	UPROPERTY()
	FDateTime StartTime;

	UPROPERTY()
	FDateTime EndTime;

public:
	static bool FromJson(const FString& InJsonString, FBeamSession& OutBeamSession);

	bool FromJson(const FString& InJsonString);

public:
	static void Test(const FString& TestName, const FString& TestJson);
	static void Test_Basic();
};
