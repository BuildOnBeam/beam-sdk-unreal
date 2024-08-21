#pragma once

#include "Misc/DateTime.h"
#include "Misc/Optional.h"
#include "KeyPair.h"

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
	FBeamSession();
	FBeamSession(FString& InJsonString);
	FBeamSession(class PlayerClientSessionsApi::GetActiveSessionResponse& ApiResponse);

public:
	static bool FromJson(const FString& InJsonString, FBeamSession& OutBeamSession);

	bool FromJson(const FString& InJsonString);
	FString WriteJson();

	bool IsValidNow();
	bool IsOwnedBy(KeyPair keyPair);

public:
	static void Test(const FString& TestName, const FString& TestJson);
	static void Test_Basic();
	static void Test_ReadWrite();
};

struct FBeamSessionAndKeyPair
{
	TOptional<FBeamSession> BeamSession;
	KeyPair KeyPair;
};

