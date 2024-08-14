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

UBeamClient* UBeamClient::SetBeamApiKey(const FString& InPublishableApiKey)
{
	BeamApiKey = InPublishableApiKey;
	return this;
}

UBeamClient* UBeamClient::SetEnvironment(EBeamEnvironment InEnvironment)
{
	FString apiUrl;
	switch (InEnvironment)
	{
	case EBeamEnvironment::Mainnet:
		apiUrl = "https://api.onbeam.com";
		break;
	default:
		apiUrl = "https://api.testnet.onbeam.com";
		break;
	}

	BeamApiUrl = apiUrl;

	// Update the APIs
	ConfigureApi(AssetsApi);
	ConfigureApi(ExchangeApi);
	ConfigureApi(HealthApi);
	ConfigureApi(MarketplaceApi);
	ConfigureApi(SessionsApi);
	ConfigureApi(TransactionsApi);
	ConfigureApi(UsersApi);
	ConfigureApi(OperationApi);
	ConfigureApi(ConnectorApi);

	return this;
}

UBeamClient* UBeamClient::SetStorage(IBeamStorageInterface* InStorage)
{
	Storage = InStorage;
	return this;
}

UBeamClient* UBeamClient::SetDebugLogging(bool InEnable)
{
	DebugLog = InEnable;
	return this;
}

//
// ----- Async API Calls -----
//


//async UniTask<BeamResult<GetConnectionRequestResponse.StatusEnum>> ConnectUserToGameAsync(
TFuture<TBeamResult<PlayerClientGetConnectionRequestResponse::StatusEnum>> UBeamClient::ConnectUserToGameAsync(
	FString EntityId,
	int32 ChainId,
	int32 SecondsTimeout
)
{
	const auto Promise = MakeShared<TPromise<TBeamResult<PlayerClientGetConnectionRequestResponse::StatusEnum>>, ESPMode::ThreadSafe>();

// TODO: Finish porting C# to Unreal C++
#if 0 // UN/PARTIALY PORTED C# CODE
	UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Retrieving connection request"));
	PlayerClientCreateConnectionRequestResponse connRequest;
	try
	{
		connRequest = await PlayerClientConnectorApi.CreateConnectionRequestAsync(
			new PlayerClientCreateConnectionRequestInput(entityId, chainId), cancellationToken);
	}
	catch (ApiException e)
	{
		return new BeamResult<GetConnectionRequestResponse.StatusEnum>(EBeamResultType::Error, e.Message);
	}

	UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Opening %s"), *connRequest.Url);
	// open browser to connect user
	Application.OpenURL(connRequest.Url);

	auto pollingResult = await PollForResult(
		actionToPerform: () = > ConnectorApi.GetConnectionRequestAsync(connRequest.Id, cancellationToken),
		shouldRetry: res = > res.Status == GetConnectionRequestResponse.StatusEnum.Pending,
		secondsTimeout: secondsTimeout,
		secondsBetweenPolls : 1,
		cancellationToken : cancellationToken);

	UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Got polling connection request result: %s"), *pollingResult.Status.ToString());

	return new BeamResult<GetConnectionRequestResponse.StatusEnum>(pollingResult.Status);
#endif // UN/PARTIALY PORTED C# CODE

	return Promise->GetFuture();
}

//async UniTask<BeamResult<BeamSession>> GetActiveSessionAsync(
TFuture<TBeamResult<FBeamSession>> UBeamClient::GetActiveSessionAsync(
	FString entityId,
	int chainId
)
{
	const auto Promise = MakeShared<TPromise<TBeamResult<FBeamSession>>, ESPMode::ThreadSafe>();

// TODO: Finish porting C# to Unreal C++
#if 0 // UN/PARTIALY PORTED C# CODE
	UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Retrieving active session"));
	auto(activeSession, _) = await GetActiveSessionAndKeysAsync(entityId, chainId, cancellationToken);

	if (activeSession == nullptr)
	{
		UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("No active session found"));
		return new BeamResult<BeamSession>(EBeamResultType::Error, "No active session found");
	}

	return new BeamResult<BeamSession>(activeSession);
#endif // UN/PARTIALY PORTED C# CODE

	return Promise->GetFuture();
}

//async UniTask<BeamResult<CommonOperationResponse.StatusEnum>> RevokeSessionAsync(
TFuture<TBeamResult<PlayerClientCommonOperationResponse::StatusEnum>> RevokeSessionAsync(
	FString entityId,
	FString sessionAddress,
	int chainId,
	int secondsTimeout
)
{
	const auto Promise = MakeShared<TPromise<TBeamResult<PlayerClientCommonOperationResponse::StatusEnum>>, ESPMode::ThreadSafe>();

// TODO: Finish porting C# to Unreal C++
#if 0 // UN/PARTIALY PORTED C# CODE
	UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Retrieving active session"));

	CommonOperationResponse operation;

	try
	{
		operation = await SessionsApi.RevokeSessionAsync(entityId,
			new RevokeSessionRequestInput(sessionAddress, chainId: chainId), cancellationToken);
	}
	catch (ApiException e)
	{
		UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Failed RevokeSessionAsync: %s %s"), *e.Message, *e.ErrorContent);
		return new BeamResult<CommonOperationResponse.StatusEnum>(EBeamResultType::Error, e.Message);
	}

	auto result = await SignOperationUsingBrowserAsync(operation, secondsTimeout, cancellationToken);
	return result;
#endif // UN/PARTIALY PORTED C# CODE

	return Promise->GetFuture();
}

//async UniTask<BeamResult<BeamSession>> CreateSessionAsync(
TFuture<TBeamResult<FBeamSession>> UBeamClient::CreateSessionAsync(
	FString entityId,
	int chainId,
	int secondsTimeout
)
{
	//const TSharedPtr<TPromise<TTuple<FHttpResponsePtr, bool>>, ESPMode::ThreadSafe> Promise = MakeShared<TPromise<TTuple<FHttpResponsePtr, bool>>, ESPMode::ThreadSafe>();
	const auto Promise = MakeShared<TPromise<TBeamResult<FBeamSession>>, ESPMode::ThreadSafe>();

#if 0 // TODO: Port
	UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Retrieving active session"));
	auto(activeSession, _) = await GetActiveSessionAndKeysAsync(entityId, chainId, cancellationToken);

	if (activeSession != nullptr)
	{
		UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Already has an active session, ending early"));
		return new BeamResult<BeamSession>(EBeamResultType::Error, "Already has an active session")
		{
			Result = activeSession
		};
	}
#endif

	UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("No active session found, refreshing local KeyPair"));

	// refresh keypair to make sure we have no conflicts with existing sessions
	KeyPair newKeyPair;
	GetOrCreateSigningKeyPair(newKeyPair, entityId, true);

	//PlayerClientGenerateSessionUrlRequestInput GenerateSessionUrlRequestInput;
	////GenerateSessionUrlRequestInput.Address = newKeyPair.Account.Address;
	//GenerateSessionUrlRequestInput.Address = newKeyPair.GetAddress().c_str();
	//GenerateSessionUrlRequestInput.ChainId = chainId;


	PlayerClientSessionsApi::CreateSessionRequestRequest request;
	request.EntityId = entityId;
	request.PlayerClientGenerateSessionUrlRequestInput.Address = newKeyPair.GetAddress().c_str();
	request.PlayerClientGenerateSessionUrlRequestInput.ChainId = chainId;

	TBeamResult<FBeamSession> beamResultModel;


	SessionsApi->CreateSessionRequest(request,
		PlayerClientSessionsApi::FCreateSessionRequestDelegate::CreateLambda(
		[&, Promise](const PlayerClientSessionsApi::CreateSessionRequestResponse& response)
		{
			const PlayerClientGenerateSessionRequestResponse& model = response.Content;

			//if (response.GetHttpResponseCode() == 200 /*.IsSuccessful()*/)
			if (response.IsSuccessful())
			{
				//FBeamSession beamSession;
				//beamSession.FromJson(response.Content);

				//TBeamResult<FBeamSession> res = TBeamResult<FBeamSession>(beamSession);
				TBeamResult<FBeamSession> res;
				Promise->SetValue(res);

				/*
				auto res = await SessionsApi.CreateSessionRequestAsync(entityId,
					new GenerateSessionUrlRequestInput(newKeyPair.Account.Address, chainId), cancellationToken);

				UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Created session request: %s to check for session result"), *beamSession.Id);
				beamSessionRequest = res;
				*/
			}
			else
			{
				/*
				UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Failed creating session request: %s %s"), *e.Message, *e.ErrorContent);
				return new BeamResult<BeamSession>(e);
				*/
			}
		}));


#if 0 // TODO: Port
	// retrieve operation Id to pass further and track result
	GenerateSessionRequestResponse beamSessionRequest;
	try
	{
		auto res = await SessionsApi.CreateSessionRequestAsync(entityId,
			new GenerateSessionUrlRequestInput(newKeyPair.Account.Address, chainId), cancellationToken);

		UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Created session request: %s to check for session result"), *res.Id);
		beamSessionRequest = res;
	}
	catch (ApiException e)
	{
		UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Failed creating session request: %s %s"), *e.Message, *e.ErrorContent);
		return new BeamResult<BeamSession>(e);
	}

	UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Opening %s", *beamSessionRequest.Url);
	// open identity.onbeam.com
	Application.OpenURL(beamSessionRequest.Url);

	TBeamResult<FBeamSession> beamResultModel;

	UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Started polling for Session creation result"));
	// start polling for results of the operation
	auto error = false;

	auto pollingResult = await PollForResult(
		actionToPerform: () = > SessionsApi.GetSessionRequestAsync(beamSessionRequest.Id, cancellationToken),
		shouldRetry: res = > res.Status == GetSessionRequestResponse.StatusEnum.Pending,
		secondsTimeout: secondsTimeout,
		secondsBetweenPolls : 1,
		cancellationToken : cancellationToken);

	if (pollingResult == nullptr)
	{
		return new BeamResult<BeamSession>(EBeamResultType::Error,
			"Polling for created session encountered an error or timed out");
	}

	switch (pollingResult.Status)
	{
	case GetSessionRequestResponse.StatusEnum.Pending:
		beamResultModel.Status = EBeamResultType::Pending;
		break;
	case GetSessionRequestResponse.StatusEnum.Accepted:
		beamResultModel.Status = EBeamResultType::Success;
		break;
	case GetSessionRequestResponse.StatusEnum.Error:
		beamResultModel.Status = EBeamResultType::Error;
		beamResultModel.Error = "Encountered an error when requesting a session";
		error = true;
		break;
	default:
		throw new ArgumentOutOfRangeException();
	}

	UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Retrieving newly created Session"));
	// retrieve newly created session
	if (!error)
	{
		auto(beamSession, _) = await GetActiveSessionAndKeysAsync(entityId, chainId, cancellationToken);
		if (beamSession != nullptr)
		{
			beamResultModel.Result = beamSession;
			UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Retrieved a session: %s, valid from: %s, to: %s"),
				*beamSession.SessionAddress,
				*beamSession.StartTime,
				*beamSession.EndTime);
		}
		else
		{
			beamResultModel.Error = "Could not retrieve session after it was created";
			beamResultModel.Status = EBeamResultType::Error;
		}
	}

	return beamResultModel;
#endif

	return Promise->GetFuture();
}




//async UniTask<BeamResult<CommonOperationResponse.StatusEnum>> SignOperationAsync(
TFuture<TBeamResult<PlayerClientCommonOperationResponse::StatusEnum>> UBeamClient::SignOperationAsync(FString entityId, FString operationId, int chainId, EBeamOperationSigningBy, int secondsTimeout)
{
	const auto Promise = MakeShared<TPromise<TBeamResult<PlayerClientCommonOperationResponse::StatusEnum>>, ESPMode::ThreadSafe>();

#if 0
	CommonOperationResponse operation;
	UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Retrieving operation(%s)"), *operationId);
	try
	{
		auto res = await OperationApi.GetOperationAsync(operationId, cancellationToken);
		operation = res;
	}
	catch (ApiException e)
	{
		if (e.ErrorCode == 404)
		{
			UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("No operation(%s) was found, ending"), *operationId);
			return new BeamResult<CommonOperationResponse.StatusEnum>
			{
				Status = EBeamResultType::Error,
				Error = "Operation was not found"
			};
		}

		UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Encountered an error retrieving operation(%s): %s %s"), *operationId, *e.Message, e.ErrorContent);
		return new BeamResult<CommonOperationResponse.StatusEnum>(e);
	}

	if (signingBy is OperationSigningBy.Auto or OperationSigningBy.Session)
	{
		UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Retrieving active session"));
		auto(activeSession, activeSessionKeyPair) =
			await GetActiveSessionAndKeysAsync(entityId, chainId, cancellationToken);

		auto hasActiveSession = activeSessionKeyPair != nullptr && activeSession != nullptr;
		if (hasActiveSession)
		{
			UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Has an active session until: %s, using it to sign the operation"), *activeSession.EndTime);
			return await SignOperationUsingSessionAsync(operation, activeSessionKeyPair, cancellationToken);
		}
	}

	if (signingBy is OperationSigningBy.Auto or OperationSigningBy.Browser)
	{
		UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("No active session found, using browser to sign the operation"));
		return await SignOperationUsingBrowserAsync(operation, secondsTimeout, cancellationToken);
	}

	UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("No active session found, %s set to %s"), *nameof(signingBy), *signingBy.ToString());
	return new BeamResult<CommonOperationResponse.StatusEnum>
	{
		Result = CommonOperationResponse.StatusEnum.Error,
		Status = EBeamResultType::Error,
		Error = FString::Printf(TEXT("No active session found, %s set to %s"), *nameof(signingBy), *signingBy.ToString())
	};
#endif

	return Promise->GetFuture();
}

/// Clears any details of local Session like private key, or Session validity details. Useful when f.e. switching users on the same device.
///  @param[in]		entityId		EntityId
void UBeamClient::ClearLocalSession(FString EntityId)
{
	if (Storage)
	{
		Storage->Delete(FBeamConstants::Storage::BeamSession + EntityId);
		Storage->Delete(FBeamConstants::Storage::BeamSigningKey + EntityId);
	}
}



//async UniTask<BeamResult<CommonOperationResponse.StatusEnum>> SignOperationUsingBrowserAsync(
TFuture<TBeamResult<PlayerClientCommonOperationResponse::StatusEnum>> UBeamClient::SignOperationUsingBrowserAsync(
	PlayerClientCommonOperationResponse operation,
	int secondsTimeout
)
{
	const auto Promise = MakeShared<TPromise<TBeamResult<PlayerClientCommonOperationResponse::StatusEnum>>, ESPMode::ThreadSafe>();

// TODO: Finish porting C# to Unreal C++
#if 0 // UN/PARTIALY PORTED C# CODE
	const FString& url = operation.Url;
	UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Opening %s..."), *url);

	// open identity.onbeam.com, give it operation id
	Application.OpenURL(url);

	// start polling for results of the operation
	FDateTime now = FDateTime::Now();
	//var now = DateTimeOffset.Now;
	auto pollingResult = await PollForResult(
		actionToPerform: () = > OperationApi.GetOperationAsync(operation.Id, cancellationToken),
		shouldRetry: res = > res == nullptr ||
		res.Status != CommonOperationResponse.StatusEnum.Pending ||
		res.Status == CommonOperationResponse.StatusEnum.Pending &&
		res.UpdatedAt != nullptr && res.UpdatedAt > now,
		secondsTimeout: secondsTimeout,
		secondsBetweenPolls : 1,
		cancellationToken : cancellationToken);

	//auto pollingStatus = pollingResult ? .Status;
	auto pollingStatus = pollingResult ? pollingResult.Status : CommonOperationResponse::StatusEnum::Error;

	UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Got operation({operation.Id}) result: %s"), *pollingStatus.ToString());
	auto beamResult = new BeamResult<CommonOperationResponse.StatusEnum>(pollingStatus);

	switch (pollingStatus)
	{
	case CommonOperationResponse::StatusEnum::Pending:
	case CommonOperationResponse::StatusEnum::Executed:
	case CommonOperationResponse::StatusEnum::Rejected:
	case CommonOperationResponse::StatusEnum::Signed:
		beamResult.Status = EBeamResultType::Success;
		break;
	case CommonOperationResponse::StatusEnum::Error:
		beamResult.Status = EBeamResultType::Error;
		beamResult.Error = TEXT("Operation encountered an error");
		break;
	default:
		beamResult.Status = EBeamResultType::Error;
		beamResult.Error = TEXT("Polling for operation encountered an error or timed out");
		break;
	}

	return beamResult;
#endif // UN/PARTIALY PORTED C# CODE

	return Promise->GetFuture();
}

//async UniTask<BeamResult<CommonOperationResponse.StatusEnum>> SignOperationUsingSessionAsync(
TFuture<TBeamResult<PlayerClientCommonOperationResponse::StatusEnum>> UBeamClient::SignOperationUsingSessionAsync(
	PlayerClientCommonOperationResponse operation,
	KeyPair activeSessionKeyPair
)
{
	const auto Promise = MakeShared<TPromise<TBeamResult<PlayerClientCommonOperationResponse::StatusEnum>>, ESPMode::ThreadSafe>();

// TODO: Finish porting C# to Unreal C++
#if 0 // UN/PARTIALY PORTED C# CODE
	if (operation && operation.Transactions && operation.Transactions.Any() != true)
	{
		UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Operation(%s) has no transactions to sign, ending"), *operation.Id);
		return new BeamResult<CommonOperationResponse.StatusEnum>
		{
			Result = CommonOperationResponse.StatusEnum.Error,
			Status = EBeamResultType::Error,
			Error = TEXT("Operation has no transactions to sign")
		};
	}

	auto confirmationModel = new ConfirmOperationRequest(
		ConfirmOperationRequest.StatusEnum.Pending,
		transactions: new List<ConfirmOperationRequestTransactionsInner>());

	for (auto& transaction : operation.Transactions)
	{
		UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Signing operation(%s) transaction(%s)..."), *operation.Id, *transaction.ExternalId);
		try
		{
			FString signature;
			switch (transaction.Type)
			{
			case CommonOperationResponseTransactionsInner.TypeEnum.OpenfortRevokeSession:
				throw new Exception(FString::Printf(TEXT("Revoke Session Operation has to be performed via %s() method only"), *nameof(RevokeSessionAsync));
			case CommonOperationResponseTransactionsInner.TypeEnum.OpenfortTransaction:
				signature = activeSessionKeyPair.SignMessage(Convert.ToString(transaction.Data));
				break;
			case CommonOperationResponseTransactionsInner.TypeEnum.OpenfortReservoirOrder:
				signature = activeSessionKeyPair.SignMarketplaceTransactionHash(transaction.Hash);
				break;
			default:
				throw new ArgumentOutOfRangeException();
			}

			confirmationModel.Transactions.Add(new ConfirmOperationRequestTransactionsInner(transaction.Id, signature));
		}
		catch (ApiException e)
		{
			UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Encountered an error when signing transaction(%s): %s %s"), *transaction.Id, *e.Message, *e.ErrorContent);
			return new BeamResult<CommonOperationResponse.StatusEnum>(e, TEXT("Encountered an exception while approving %s"), *transaction.Type.ToString());
		}
	}

	UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Confirming operation(%s)..."), *operation.Id);
	try
	{
		auto res = await OperationApi.ProcessOperationAsync(operation.Id, confirmationModel,
			cancellationToken);
		auto didFail = res.Status != CommonOperationResponse.StatusEnum.Executed &&
			res.Status != CommonOperationResponse.StatusEnum.Signed &&
			res.Status != CommonOperationResponse.StatusEnum.Pending;

		UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Confirmed operation(%s), status: %s"), *operation.Id, *res.Status.ToString());
		return new BeamResult<CommonOperationResponse.StatusEnum>
		{
			Status = didFail ? EBeamResultType::Error : EBeamResultType::Success,
			Result = res.Status
		};
	}
	catch (ApiException e)
	{
		UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Confirming operation(%s) encountered an error: %s"), *operation.Id, *e.ErrorContent);
		return new BeamResult<CommonOperationResponse.StatusEnum>
		{
			Status = EBeamResultType::Error,
			Error = e.Message ? e.Message : FString::Printf(TEXT("Encountered unknown error when confirming operation %s"), *operation.Id)
		};
	}
#endif // UN/PARTIALY PORTED C# CODE

	return Promise->GetFuture();
}

// TODO: Decide whether to keep, then Finish porting C# to Unreal C++ if needed.
#if 0 // Disabled - AND - UN/PARTIALY PORTED C# CODE
/// Will retry or return nullptr if received 404.
static async UniTask<T> UBeamClient::PollForResult<T>(
	Func<UniTask<T>> actionToPerform,
	Func<T, bool> shouldRetry,
	int secondsTimeout = DefaultTimeoutInSeconds,
	int secondsBetweenPolls = 1,
	CancellationToken cancellationToken = default)
where T : class
{
	await UniTask.Delay(2000, cancellationToken: cancellationToken);

	auto endTime = FDateTime::Now().AddSeconds(secondsTimeout);

	while ((endTime - FDateTime::Now()).TotalSeconds > 0)
	{
		T result;
		try
		{
			result = await actionToPerform.Invoke();
		}
		catch (ApiException e)
		{
			if (e.ErrorCode == 404)
			{
				return nullptr;
			}

			throw;
		}

		auto retry = shouldRetry.Invoke(result);
		if (!retry)
		{
			return result;
		}

		await UniTask.Delay(secondsBetweenPolls * 1000, cancellationToken: cancellationToken);
	}

	return nullptr;
}
#endif // Disabled - AND - UN/PARTIALY PORTED C# CODE

//async UniTask<(BeamSession, KeyPair)> UBeamClient::GetActiveSessionAndKeysAsync(
TFuture<TTuple<FBeamSession, KeyPair>> UBeamClient::GetActiveSessionAndKeysAsync(
	FString entityId,
	int chainId
)
{
	const auto Promise = MakeShared<TPromise<TTuple<FBeamSession, KeyPair>>, ESPMode::ThreadSafe>();

// TODO: Finish porting C# to Unreal C++
#if 0 // UN/PARTIALY PORTED C# CODE
	BeamSession beamSession = nullptr;
	auto sessionInfo = Storage.Get(FBeamConstants::Storage::BeamSession + entityId);
	if (sessionInfo != nullptr)
	{
		beamSession = JsonConvert.DeserializeObject<BeamSession>(sessionInfo);
	}

	KeyPair keyPair;
	GetOrCreateSigningKeyPair(keyPair, entityId);

	// if session is no longer valid, check if we have one saved in the API
	if (!beamSession.IsValidNow())
	{
		try
		{
			auto res = await SessionsApi.GetActiveSessionAsync(entityId, keyPair.Account.Address,
				chainId, cancellationToken);
			beamSession = new BeamSession
			{
				Id = res.Id,
				StartTime = res.StartTime,
				EndTime = res.EndTime,
				SessionAddress = res.SessionAddress
			};
		}
		catch (ApiException e)
		{
			UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("GetActiveSessionInfo returned: %s %s"), *e.Message, *e.ErrorContent);
		}
	}

	// make sure session we just retrieved is valid and owned by current KeyPair
	if (beamSession.IsValidNow() && beamSession.IsOwnedBy(keyPair))
	{
		Storage.Set(FBeamConstants::Storage::BeamSession + entityId, JsonConvert.SerializeObject(beamSession));
		return (beamSession, keyPair);
	}

	// if session is not valid or owned by different KeyPair, remove it from cache
	Storage.Delete(FBeamConstants::Storage::BeamSession + entityId);
	return (nullptr, keyPair);
#endif // UN/PARTIALY PORTED C# CODE

	return Promise->GetFuture();
}

void UBeamClient::GetOrCreateSigningKeyPair(KeyPair& OutKeyPair, FString InEntityId, bool InRefresh)
{
	if (!InRefresh)
	{
		FString privateKey = Storage->Get(FBeamConstants::Storage::BeamSigningKey + InEntityId);
		if (!privateKey.IsEmpty())
		{
			//return KeyPair.Load(privateKey);
			OutKeyPair.Initialize(std::string(TCHAR_TO_UTF8(*privateKey)));
		}
	}

	OutKeyPair.Generate();
	Storage->Set(FBeamConstants::Storage::BeamSigningKey + InEntityId, OutKeyPair.GetPrivateKeyHex().c_str());
}
