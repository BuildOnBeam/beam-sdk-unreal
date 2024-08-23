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
#include "TimerManager.h"
#include "Engine/World.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

#include "GenericPlatform/GenericPlatformProcess.h"

DEFINE_LOG_CATEGORY(LogBeamClient);

UE_DISABLE_OPTIMIZATION

UBeamClient::UBeamClient()
{
	SetEnvironment(EBeamEnvironment::Testnet);
}


void UBeamClient::LaunchURL(const FString& Url, FString& Params, FString& OutError)
{
	FPlatformProcess::LaunchURL(*Url, *Params, &OutError);
}


FString UBeamClient::LaunchURL(const FString& Url)
{
	FString Params, LaunchUrlError;
	FPlatformProcess::LaunchURL(*Url, *Params, &LaunchUrlError);
	return LaunchUrlError;
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


TFuture<BeamConnectionResult> UBeamClient::ConnectUserToGameAsync(FString entityId, int32 chainId, int32 secondsTimeout)
{
	const auto Promise = MakeShared<TPromise<BeamConnectionResult>, ESPMode::ThreadSafe>();

// TODO: Finish porting C# to Unreal C++
#if 0 // UN/PARTIALY PORTED C# CODE
	UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Retrieving connection request"));

	PlayerClientCreateConnectionRequestResponse connRequest;

	PlayerClientCreateConnectionRequestInput input;
	input.EntityId = entityId;
	input.ChainId = chainId;

	ConnectorApi->CreateConnectionRequest(input,
		DELEGATE([](const PlayerClientCreateConnectionRequestResponse& res)
	{
	}));
	
	
	try
	{
		connRequest = await PlayerClientConnectorApi.CreateConnectionRequestAsync(
			new PlayerClientCreateConnectionRequestInput(entityId, chainId), cancellationToken);
	}
	catch (ApiException e)
	{
		return BeamConnectionResult(EBeamResultType::Error, e.Message);
	}

	UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Opening %s"), *connRequest.Url);
	// open browser to connect user
	Application.OpenURL(connRequest.Url);

	auto pollingResult = await PollForResult(
		actionToPerform: () = > ConnectorApi.GetConnectionRequestAsync(connRequest.Id, cancellationToken),
		shouldRetry: res = > res.Status == GetConnectionRequestResponse::StatusEnum::Pending,
		secondsTimeout: secondsTimeout,
		secondsBetweenPolls : 1,
		cancellationToken : cancellationToken);

	UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Got polling connection request result: %s"), *pollingResult.Status.ToString());

	return BeamConnectionResult(pollingResult.Status);
#endif // UN/PARTIALY PORTED C# CODE

	return Promise->GetFuture();
}


TFuture<BeamSessionResult> UBeamClient::GetActiveSessionAsync(FString entityId, int chainId)
{
	auto resultFuture = Async(EAsyncExecution::Thread, [&, entityId, chainId]()
	{
		UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Retrieving active session"));
		auto sessionKeys = GetActiveSessionAndKeysAsync(entityId, chainId).Get();
		if (!sessionKeys.BeamSession.IsSet())
		{
			UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("No active session found"));
			return BeamSessionResult(EBeamResultType::Error, "No active session found");
		}
		else
		{
			return BeamSessionResult(sessionKeys.BeamSession.GetValue());
		}
	});
	return resultFuture;
}


TFuture<BeamOperationResult> UBeamClient::RevokeSessionAsync(FString entityId, FString sessionAddress, int chainId, int secondsTimeout)
{
	const auto Promise = MakeShared<TPromise<BeamOperationResult>, ESPMode::ThreadSafe>();

	UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Retrieving active session"));

	PlayerClientSessionsApi::RevokeSessionRequest request;
	request.EntityId = entityId;
	request.PlayerClientRevokeSessionRequestInput.Address = sessionAddress;
	request.PlayerClientRevokeSessionRequestInput.ChainId = chainId;

	SessionsApi->RevokeSession(request,
		PlayerClientSessionsApi::FRevokeSessionDelegate::CreateLambda([&, Promise, secondsTimeout](const PlayerClientSessionsApi::RevokeSessionResponse& res)
	{
		BeamOperationResult result;
		PlayerClientCommonOperationResponse operation = res.Content;
		if (res.IsSuccessful() && IsOk(res.GetHttpResponseCode()))
		{
			result = SignOperationUsingBrowserAsync(operation, secondsTimeout).Get();
		}
		else
		{
			int32 errorCode = (int32)res.GetHttpResponseCode();
			FString errorMessage = res.GetHttpResponse()->GetContentAsString();
			UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Failed RevokeSessionAsync: %d: %s"), errorCode, *errorMessage);

			result = BeamOperationResult(EBeamResultType::Error, errorMessage);
		}

		// Resolve the promise on the game thread for convienence.
		AsyncTask(ENamedThreads::GameThread, [Promise, result]()
		{
			Promise->SetValue(result);
		});
	}));
	return Promise->GetFuture();
}


TFuture<BeamSessionResult> UBeamClient::CreateSessionAsync(FString entityId, int chainId, int secondsTimeout)
{
	const auto Promise = MakeShared<TPromise<BeamSessionResult>, ESPMode::ThreadSafe>();

	// Run on another thread so we can use concepts like sleep() when retrying requests without blocking the game thread
	auto resultFuture = Async(EAsyncExecution::Thread, [&, Promise, entityId, chainId, secondsTimeout]()
	{
		UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("CreateSessionAsync: Retrieving active session: "
			"entityId=%s, chainId=%d, secondsTimeout=%d"), *entityId, chainId, secondsTimeout);
		{
			auto sessionKeys = GetActiveSessionAndKeysAsync(entityId, chainId).Get();
			auto& activeSession = sessionKeys.BeamSession;
			if (activeSession.IsSet())
			{
				UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Already has an active session, ending early"));

				BeamSessionResult result(EBeamResultType::Error, "Already has an active session");
				result.Result = *activeSession;
				return result;
			}
		}

		UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("No active session found, refreshing local KeyPair"));

		// Refresh keypair to make sure we have no conflicts with existing sessions.
		KeyPair newKeyPair;
		GetOrCreateSigningKeyPair(newKeyPair, entityId, true);

		PlayerClientSessionsApi::CreateSessionRequestRequest request;
		request.EntityId = entityId;
		request.PlayerClientGenerateSessionUrlRequestInput.Address = newKeyPair.GetAddress().c_str();
		request.PlayerClientGenerateSessionUrlRequestInput.ChainId = chainId;

		const auto resPromise = MakeShared<TPromise<PlayerClientSessionsApi::CreateSessionRequestResponse>, ESPMode::ThreadSafe>();
		auto resFuture = resPromise->GetFuture();
		SessionsApi->CreateSessionRequest(request,
			PlayerClientSessionsApi::FCreateSessionRequestDelegate::CreateLambda(
			[&, resPromise](const PlayerClientSessionsApi::CreateSessionRequestResponse& response)
		{
			resPromise->SetValue(response);
		}));

		auto res = resFuture.Get();
		if (!res.IsSuccessful() || !IsOk(res.GetHttpResponseCode()))
		{
			int32 errorCode = (int32)res.GetHttpResponseCode();
			FString errorMessage = res.GetHttpResponse()->GetContentAsString();
			UE_CLOG(DebugLog, LogBeamClient, Error, TEXT("Failed CreateSessionRequest: %d %s"), errorCode, *errorMessage);
			return BeamSessionResult(EBeamResultType::Error, "Failed to create session request");
		}
		
		if (res.Content.Status == GenerateSessionRequestStatusEnum::Error)
		{
			FString errorMessage = res.GetHttpResponse()->GetContentAsString();
			UE_CLOG(DebugLog, LogBeamClient, Error, TEXT("Failed creating session request: %s"), *errorMessage);
			return BeamSessionResult(EBeamResultType::Error, "CreateSession returned status=Error");
		}

		UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Created session request: %s to check for session result"), *res.Content.Id);
		PlayerClientGenerateSessionRequestResponse beamSessionRequest = res.Content;

		UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Opening %s"), *beamSessionRequest.Url);

		// Open "identity.onbeam.com".
		FString launchErrors = LaunchURL(beamSessionRequest.Url);

		// Start polling for results of the operation.
		UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Started polling for Session creation result"));

		bool error = false;

		PlayerClientSessionsApi::GetSessionRequestRequest gsRequest;
		gsRequest.RequestId = beamSessionRequest.Id;

		auto cancellationToken = MakeShared<FBeamCancellationToken>();

		// This action will be polled in the PollForResult call below.
		auto actionToPerform = [&, gsRequest, cancellationToken]() -> TFuture<PlayerClientSessionsApi::GetSessionRequestResponse>
		{
			const auto gsPromise = MakeShared<TPromise<PlayerClientSessionsApi::GetSessionRequestResponse>, ESPMode::ThreadSafe>();
			SessionsApi->GetSessionRequest(gsRequest, PlayerClientSessionsApi::FGetSessionRequestDelegate::CreateLambda(
				[&, gsPromise](const PlayerClientSessionsApi::GetSessionRequestResponse& GetSessionResponse)
			{
				UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("GetSessionRequestResponse: %s"), *GetSessionResponse.GetHttpResponse()->GetContentAsString());
				gsPromise->SetValue(GetSessionResponse);
			}));
			return gsPromise->GetFuture();
		};

		// This controls whether the above action should continue to poll.
		auto shouldRetry = [&](const PlayerClientSessionsApi::GetSessionRequestResponse& res) -> bool
		{
			FString status = PlayerClientGetSessionRequestResponse::EnumToString(res.Content.Status);
			UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("GetSessionRequestResponse: Status=%s"), *status);
			return res.Content.Status == GetSessionRequestStatusEnum::Pending;
		};

		// This call initiates the polling, and waits for the result.
		auto pollingResult = PollForResult<PlayerClientSessionsApi::GetSessionRequestResponse>(actionToPerform, shouldRetry, secondsTimeout, 1, cancellationToken).Get();
		if (!pollingResult.IsSet())
		{
			return BeamSessionResult(EBeamResultType::Error, "Polling for created session encountered an error or timed out");
		}

		BeamSessionResult beamResultModel;
		switch (pollingResult.GetValue().Content.Status)
		{
		case GetSessionRequestStatusEnum::Pending:
			beamResultModel.Status = EBeamResultType::Pending;
			break;
		case GetSessionRequestStatusEnum::Accepted:
			beamResultModel.Status = EBeamResultType::Success;
			break;
		case GetSessionRequestStatusEnum::Error:
		default:
			beamResultModel.Status = EBeamResultType::Error;
			beamResultModel.Error = "Encountered an error when requesting a session";
			error = true;
			break;
		}

		UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Retrieving newly created Session"));

		// Retrieve newly created session.
		if (!error)
		{
			auto sessionKeys = GetActiveSessionAndKeysAsync(entityId, chainId).Get();
			if (sessionKeys.BeamSession.IsSet())
			{
				auto& beamSession = sessionKeys.BeamSession.GetValue();
				beamResultModel.Result = beamSession;
				UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Retrieved a session: %s, valid from: %s, to: %s"),
					*beamSession.SessionAddress,
					*FText::AsDateTime(beamSession.StartTime).ToString(),
					*FText::AsDateTime(beamSession.EndTime).ToString());
			}
			else
			{
				beamResultModel.Error = "Could not retrieve session after it was created";
				beamResultModel.Status = EBeamResultType::Error;
			}
		}

		return beamResultModel;
	})
	.Next([Promise](const BeamSessionResult& result)
	{
		// Resolve the promise on the game thread for convienence.
		AsyncTask(ENamedThreads::GameThread, [Promise, result]()
		{
			Promise->SetValue(result);
		});
	});
	return Promise->GetFuture();
}


TFuture<BeamOperationResult> UBeamClient::SignOperationAsync(FString entityId, FString operationId, int chainId, EBeamOperationSigningBy signingBy, int secondsTimeout)
{
	const auto Promise = MakeShared<TPromise<BeamOperationResult>, ESPMode::ThreadSafe>();
	auto resultFuture = Async(EAsyncExecution::Thread, [&, Promise, entityId, operationId, chainId, signingBy, secondsTimeout]()
	{
		BeamOperationResult result;



#if 0
	PlayerClientCommonOperationResponse operation;
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
			return BeamOperationResult
			{
				Status = EBeamResultType::Error,
				Error = "Operation was not found"
			};
		}

		UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Encountered an error retrieving operation(%s): %s %s"), *operationId, *e.Message, e.ErrorContent);
		return BeamOperationResult(e);
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
	return BeamOperationResult
	{
		Result = CommonOperationStatusEnum::Error,
		Status = EBeamResultType::Error,
		Error = FString::Printf(TEXT("No active session found, %s set to %s"), *nameof(signingBy), *signingBy.ToString())
	};
#endif



		return result;
	})
	.Next([Promise](const BeamOperationResult& result)
	{
		// Resolve the promise on the game thread for convienence.
		AsyncTask(ENamedThreads::GameThread, [Promise, result]()
		{
			Promise->SetValue(result);
		});
	});
	return Promise->GetFuture();
}


void UBeamClient::ClearLocalSession(FString EntityId)
{
	if (Storage)
	{
		Storage->Delete(FBeamConstants::Storage::BeamSession + EntityId);
		Storage->Delete(FBeamConstants::Storage::BeamSigningKey + EntityId);
		Storage->Save();
	}
}


TFuture<BeamOperationResult> UBeamClient::SignOperationUsingBrowserAsync(PlayerClientCommonOperationResponse operation, int secondsTimeout)
{
	const auto Promise = MakeShared<TPromise<BeamOperationResult>, ESPMode::ThreadSafe>();

// TODO: Finish porting C# to Unreal C++
#if 0 // UN/PARTIALY PORTED C# CODE
	const FString& url = operation.Url;
	UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Opening %s..."), *url);

	// open identity.onbeam.com, give it operation id
	Application.OpenURL(url);

	// start polling for results of the operation
	FDateTime now = FDateTime::UtcNow();
	//var now = DateTimeOffset.Now;
	auto pollingResult = await PollForResult(
		actionToPerform: () = > OperationApi.GetOperationAsync(operation.Id, cancellationToken),
		shouldRetry: res = > res == nullptr ||
		res.Status != CommonOperationStatusEnum::Pending ||
		res.Status == CommonOperationStatusEnum::Pending &&
		res.UpdatedAt != nullptr && res.UpdatedAt > now,
		secondsTimeout: secondsTimeout,
		secondsBetweenPolls : 1,
		cancellationToken : cancellationToken);

	//auto pollingStatus = pollingResult ? .Status;
	auto pollingStatus = pollingResult ? pollingResult.Status : CommonOperationStatusEnum::Error;

	UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Got operation({operation.Id}) result: %s"), *pollingStatus.ToString());
	auto beamResult = BeamOperationResult(pollingStatus);

	switch (pollingStatus)
	{
	case CommonOperationStatusEnum::Pending:
	case CommonOperationStatusEnum::Executed:
	case CommonOperationStatusEnum::Rejected:
	case CommonOperationStatusEnum::Signed:
		beamResult.Status = EBeamResultType::Success;
		break;
	case CommonOperationStatusEnum::Error:
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


TFuture<BeamOperationResult> UBeamClient::SignOperationUsingSessionAsync(PlayerClientCommonOperationResponse operation, KeyPair activeSessionKeyPair)
{
	const auto Promise = MakeShared<TPromise<BeamOperationResult>, ESPMode::ThreadSafe>();

// TODO: Finish porting C# to Unreal C++
#if 0 // UN/PARTIALY PORTED C# CODE
	if (operation && operation.Transactions && operation.Transactions.Any() != true)
	{
		UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Operation(%s) has no transactions to sign, ending"), *operation.Id);
		return BeamOperationResult
		{
			Result = CommonOperationStatusEnum::Error,
			Status = EBeamResultType::Error,
			Error = TEXT("Operation has no transactions to sign")
		};
	}

	auto confirmationModel = new ConfirmOperationRequest(
		ConfirmOperationStatusEnum::Pending,
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
			return BeamOperationResult(e, TEXT("Encountered an exception while approving %s"), *transaction.Type.ToString());
		}
	}

	UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Confirming operation(%s)..."), *operation.Id);
	try
	{
		auto res = await OperationApi.ProcessOperationAsync(operation.Id, confirmationModel,
			cancellationToken);
		auto didFail = res.Status != CommonOperationStatusEnum::Executed &&
			res.Status != CommonOperationStatusEnum::Signed &&
			res.Status != CommonOperationStatusEnum::Pending;

		UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Confirmed operation(%s), status: %s"), *operation.Id, *res.Status.ToString());
		return BeamOperationResult
		{
			Status = didFail ? EBeamResultType::Error : EBeamResultType::Success,
			Result = res.Status
		};
	}
	catch (ApiException e)
	{
		UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Confirming operation(%s) encountered an error: %s"), *operation.Id, *e.ErrorContent);
		return BeamOperationResult
		{
			Status = EBeamResultType::Error,
			Error = e.Message ? e.Message : FString::Printf(TEXT("Encountered unknown error when confirming operation %s"), *operation.Id)
		};
	}
#endif // UN/PARTIALY PORTED C# CODE

	return Promise->GetFuture();
}


TFuture<FBeamSessionAndKeyPair> UBeamClient::GetActiveSessionAndKeysAsync(FString entityId, int chainId)
{
	auto resultFuture = Async(EAsyncExecution::Thread, [&, entityId, chainId]()
	{
		FBeamSessionAndKeyPair sessionKeys;
		KeyPair& keyPair = sessionKeys.KeyPair;

		FString sessionInfo = Storage->Get(FBeamConstants::Storage::BeamSession + entityId);
		if (!sessionInfo.IsEmpty())
		{
			sessionKeys.BeamSession = FBeamSession();
			sessionKeys.BeamSession->FromJson(sessionInfo);
		}

		GetOrCreateSigningKeyPair(keyPair, entityId);

		// If session is no longer valid, check if we have one saved in the API.
		if (!sessionKeys.BeamSession.IsSet())
		{
			PlayerClientSessionsApi::GetActiveSessionRequest request;
			request.EntityId = entityId;
			request.AccountAddress = keyPair.GetAddress().c_str();
			request.ChainId = chainId;

			const auto resPromise = MakeShared<TPromise<PlayerClientSessionsApi::GetActiveSessionResponse>, ESPMode::ThreadSafe>();
			auto resFuture = resPromise->GetFuture();
			auto httpReq = SessionsApi->GetActiveSession(request,
				PlayerClientSessionsApi::FGetActiveSessionDelegate::CreateLambda(
				[&, resPromise](const PlayerClientSessionsApi::GetActiveSessionResponse& response)
			{
				resPromise->SetValue(response);
			}));
			
			auto res = resFuture.Get();
			if (res.IsSuccessful() && IsOk(res.GetHttpResponseCode()))
			{
				sessionKeys.BeamSession = FBeamSession(res);
			}
			else
			{
				int32 errorCode = (int32)res.GetHttpResponseCode();
				FString errorMessage = res.GetResponseString();
				UE_CLOG(DebugLog, LogBeamClient, Error, TEXT("GetActiveSessionInfo returned: %d %s"), errorCode, *errorMessage);
			}
		}

		if (sessionKeys.BeamSession.IsSet())
		{
			FBeamSession& beamSession = sessionKeys.BeamSession.GetValue();

			// Make sure session we just retrieved is valid and owned by current KeyPair.
			if (beamSession.IsValidNow() && beamSession.IsOwnedBy(keyPair))
			{
				Storage->Set(FBeamConstants::Storage::BeamSession + entityId, beamSession.WriteJson());
				Storage->Save();
				return sessionKeys;
			}
		}

		// If session is not valid or owned by different KeyPair, remove it from cache.
		Storage->Delete(FBeamConstants::Storage::BeamSession + entityId);
		Storage->Save();
		sessionKeys.BeamSession.Reset();
		return sessionKeys;
	});
	return resultFuture;
}


void UBeamClient::GetOrCreateSigningKeyPair(KeyPair& OutKeyPair, FString InEntityId, bool InRefresh)
{
	FString entityStorageKey = FBeamConstants::Storage::BeamSigningKey + InEntityId;
	if (!InRefresh)
	{
		FString privateKey = Storage->Get(entityStorageKey);
		if (!privateKey.IsEmpty())
		{
			OutKeyPair.Initialize(std::string(TCHAR_TO_UTF8(*privateKey)));
			return;
		}
	}

	OutKeyPair.Generate();

// Allows debugging the generated keys for debug and devopment builds. (1 = On, 0 = Off [default])
#define DEBUG_KEY_GEN 0
#if !UE_BUILD_SHIPPING && DEBUG_KEY_GEN
	{
		FString address = OutKeyPair.GetAddress().c_str();
		FString publicKey = OutKeyPair.GetPublicKeyHex().c_str();
		FString privateKey = OutKeyPair.GetPrivateKeyHex().c_str();
		UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("KeyPair:\n  address:%s\n  public: %s\n  private: %s"), *address, *publicKey, *privateKey);
	}
#endif
#undef DEBUG_KEY_GEN

	Storage->Set(entityStorageKey, OutKeyPair.GetPrivateKeyHex().c_str());
	Storage->Save();
}

UE_ENABLE_OPTIMIZATION
