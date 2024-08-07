#include "BeamClient.h"

#include "BeamApiError.h"
#include "BeamEnvironment.h"
#include "BeamOperationSigningBy.h"
#include "BeamResult.h"
#include "BeamSession.h"
#include "BeamSaveGameStorage.h"
#include "BeamUtils.h"

#include "Interfaces/IHttpRequest.h"
#include "PlatformHttp.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

#include "GenericPlatform/GenericPlatformProcess.h"

DEFINE_LOG_CATEGORY(LogBeamClient);


UBeamClient::UBeamClient()
{
	SetEnvironment(EBeamEnvironment::Testnet);
}

void UBeamClient::RunTests()
{
	UE_LOG(LogBeamClient, Log, TEXT("----- RUNNING FBeamApiError TESTS -----"));
	FBeamApiError::Test_Basic();

	UE_LOG(LogBeamClient, Log, TEXT("----- RUNNING FBeamSession TESTS -----"));
	FBeamSession::Test_Basic();
}

void UBeamClient::LaunchURL(const FString& Url, FString& Params, FString& OutError)
{
	FPlatformProcess::LaunchURL(*Url, *Params, &OutError);
}



//
// --- Config ---
//

UBeamClient& UBeamClient::SetBeamApiKey(const FString& PublishableApiKey)
{
	BeamApiKey = PublishableApiKey;
	return *this;
}

UBeamClient& UBeamClient::SetEnvironment(EBeamEnvironment Environment)
{
	FString apiUrl;
	switch (Environment)
	{
	case EBeamEnvironment::Mainnet:
		apiUrl = "https://api.onbeam.com";
		break;
	default:
		apiUrl = "https://api.testnet.onbeam.com";
		break;
	}

	BeamApiUrl = apiUrl;
	return *this;
}

UBeamClient& UBeamClient::SetStorage(IBeamStorageInterface* storage)
{
	Storage = storage;
	return *this;
}

UBeamClient& UBeamClient::SetDebugLogging(bool enable)
{
	DebugLog = enable;
	return *this;
}



// TODO: Move ported API calls here when functional

