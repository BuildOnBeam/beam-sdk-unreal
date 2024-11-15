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
	FBeamSession(class PlayerClientSessionsApi::GetActiveSessionV2Response& ApiV2Response);

public:
	static bool FromJson(const FString& InJsonString, FBeamSession& OutBeamSession);

	bool FromJson(const FString& InJsonString);
	FString WriteJson();

	bool IsValidNow();
	bool IsOwnedBy(KeyPair keyPair);
};

struct FBeamSessionAndKeyPair
{
	TOptional<FBeamSession> BeamSession;
	KeyPair KeyPair;
};

