#pragma once

#include "CoreMinimal.h"

// Beam PlayerClient APIs
#include "PlayerClientAssetsApi.h"
#include "PlayerClientConnectorApi.h"
#include "PlayerClientExchangeApi.h"
#include "PlayerClientHealthApi.h"
#include "PlayerClientMarketplaceApi.h"
#include "PlayerClientOperationApi.h"
#include "PlayerClientSessionsApi.h"
#include "PlayerClientTransactionsApi.h"
#include "PlayerClientUsersApi.h"

#include "PlayerClientBaseModel.h"

// Beam PlayerClient Responses
#include "PlayerClientCheck200Response.h"
#include "PlayerClientCheck503Response.h"
#include "PlayerClientCommonActivityResponse.h"
#include "PlayerClientCommonOperationResponse.h"
#include "PlayerClientCommonStatsResponse.h"
#include "PlayerClientCreateConnectionRequestResponse.h"
#include "PlayerClientGenerateSessionRequestResponse.h"
#include "PlayerClientGetActiveSessionResponse.h"
#include "PlayerClientGetActiveSessionsResponse.h"
#include "PlayerClientGetAllUsersResponse.h"
#include "PlayerClientGetAssetListingsResponse.h"
#include "PlayerClientGetAssetResponse.h"
#include "PlayerClientGetAssetsForContractResponse.h"
#include "PlayerClientGetAssetsForUserResponse.h"
#include "PlayerClientGetAttributesResponse.h"
#include "PlayerClientGetChainCurrenciesResponse.h"
#include "PlayerClientGetConnectionRequestResponse.h"
#include "PlayerClientGetOwnerAssetsResponse.h"
#include "PlayerClientGetOwnersResponse.h"
#include "PlayerClientGetQuoteResponse.h"
#include "PlayerClientGetSessionRequestResponse.h"
#include "PlayerClientGetTransactionResponse.h"
#include "PlayerClientGetTransactionsResponse.h"
#include "PlayerClientGetUserCurrenciesResponse.h"
#include "PlayerClientGetUserNativeCurrencyResponse.h"
#include "PlayerClientGetUserResponse.h"

#include "KeyPair.h"

#include "BeamConstants.h"
#include "BeamEnvironment.h"
#include "BeamStorageInterface.h"

#include "BeamClient.generated.h"

using namespace OpenAPI;

DECLARE_LOG_CATEGORY_EXTERN(LogBeamClient, Log, All);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class BEAMSDK_API UBeamClient : public UObject
{
	GENERATED_BODY()

public:
	PlayerClientAssetsApi AssetsApi;
	PlayerClientExchangeApi ExchangeApi;
	PlayerClientHealthApi HealthApi;
	PlayerClientMarketplaceApi MarketplaceApi;
	PlayerClientSessionsApi SessionsApi;
	PlayerClientTransactionsApi TransactionsApi;
	PlayerClientUsersApi UsersApi;
	PlayerClientOperationApi OperationApi;
	PlayerClientConnectorApi ConnectorApi;

public:
	UBeamClient();


// Tests
public:
	UFUNCTION(BlueprintCallable, Category = "Test")
	void RunTests();


// Virtual methods
public:
	/// Launches a URL in a browser. (optionally override if needed)
	///  @param[in]		InUrl		The url to browse to
	///  @param[in]		InParams	The maximum radius of any agent that will be added to the crowd. [Limit: > 0]
	///  @param[out]	OutError	The navigation mesh to use for planning.
	/// @return True if the initialization succeeded.
	virtual void LaunchURL(const FString& InUrl, FString& InParams, FString& OutError);


// Config
public:

	/// Sets Publishable Beam API key on the client. WARNING: Do not use keys other than Publishable, they're meant to be private, server-side only!
	///  @param[in]		PublishableApiKey	Publishable Beam API key
	/// @return BeamClient
	UBeamClient& SetBeamApiKey(const FString& PublishableApiKey);

	/// Sets Environment on the client.
	///  @param[in]		Environment		BeamEnvironment.Mainnet or BeamEnvironment.Testnet (defaults to Testnet)
	/// @return BeamClient
	UBeamClient& SetEnvironment(EBeamEnvironment Environment);

	/// Sets custom storage for Session related information. Defaults to UBeamSaveGameStorage.
	///  @param[in]		Storage		Storage that implements IStorage
	/// @return BeamClient
	UBeamClient& SetStorage(IBeamStorageInterface* storage);

	/// Set to true, to enable Debug.Log() statements. Defaults to false.
	///  @param[in]		enable		True to enable
	/// @return BeamClient
	UBeamClient& SetDebugLogging(bool enable);


// Connection
public:

	// TODO: Finish porting C# to Unreal C++
#if 0 // UN/PARTIALY PORTED C# CODE
	/// Will connect given EntityId for your game to a User.
	/// This will also happen on first possible action signed by user in the browser.
	///  @param[in]		EntityId			Entity Id of the User performing signing
	///  @param[in]		ChainId				ChainId to perform operation on. Defaults to 13337.
	///  @param[in]		SecondsTimeout		Optional timeout in seconds, defaults to 240
	///  @param[in]		CancellationToken	Optional CancellationToken
	/// @return UniTask
	//async UniTask<BeamResult<GetConnectionRequestResponse.StatusEnum>> ConnectUserToGameAsync(
	TFuture<TBeamResult<PlayerClientGetConnectionRequestResponse::StatusEnum>> ConnectUserToGameAsync(
		FString EntityId,
		int32 ChainId = FBeamConstants::DefaultChainId,
		int32 SecondsTimeout = DefaultTimeoutInSeconds,
		CancellationToken CancellationToken = default
	)
	{
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
	}

	/// Retrieves active, valid session.
	///  @param[in]		entityId		Entity Id of the User performing signing
	///  @param[in]		chainId		ChainId to perform operation on. Defaults to 13337.
	///  @param[in]		cancellationToken		Optional CancellationToken
	/// @return UniTask
	//async UniTask<BeamResult<BeamSession>> GetActiveSessionAsync(
	async UniTask<BeamResult<BeamSession>> GetActiveSessionAsync(
		FString entityId,
		int chainId = FBeamConstants::DefaultChainId,
		CancellationToken cancellationToken = default)
	{
		UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Retrieving active session"));
		auto(activeSession, _) = await GetActiveSessionAndKeysAsync(entityId, chainId, cancellationToken);

		if (activeSession == null)
		{
			UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("No active session found"));
			return new BeamResult<BeamSession>(EBeamResultType::Error, "No active session found");
		}

		return new BeamResult<BeamSession>(activeSession);
	}

	/// Revokes given Session Address. Always opens Browser as User has to sign it with his key.
	///  @param[in]		entityId		Entity Id of the User performing signing
	///  @param[in]		sessionAddress		address of a Session to revoke
	///  @param[in]		chainId		ChainId to perform operation on. Defaults to 13337.
	///  @param[in]		secondsTimeout		Optional timeout in seconds, defaults to 240
	///  @param[in]		cancellationToken		Optional CancellationToken
	/// @return UniTask
	//async UniTask<BeamResult<CommonOperationResponse.StatusEnum>> RevokeSessionAsync(
	async UniTask<BeamResult<CommonOperationResponse.StatusEnum>> RevokeSessionAsync(
		FString entityId,
		FString sessionAddress,
		int chainId = FBeamConstants::DefaultChainId,
		int secondsTimeout = DefaultTimeoutInSeconds,
		CancellationToken cancellationToken = default)
	{
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
	}

	/// Opens an external browser to sign a Session, returns the result via callback arg.
	///  @param[in]		entityId		Entity Id of the User performing signing
	///  @param[in]		chainId		ChainId to perform operation on. Defaults to 13337.
	///  @param[in]		secondsTimeout		Optional timeout in seconds, defaults to 240
	///  @param[in]		cancellationToken		Optional CancellationToken
	/// @return UniTask
	//async UniTask<BeamResult<BeamSession>> CreateSessionAsync(
	async UniTask<BeamResult<BeamSession>> CreateSessionAsync(
		FString entityId,
		int chainId = FBeamConstants::DefaultChainId,
		int secondsTimeout = DefaultTimeoutInSeconds,
		CancellationToken cancellationToken = default)
	{
		UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Retrieving active session"));
		auto(activeSession, _) = await GetActiveSessionAndKeysAsync(entityId, chainId, cancellationToken);

		if (activeSession != null)
		{
			UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Already has an active session, ending early"));
			return new BeamResult<BeamSession>(EBeamResultType::Error, "Already has an active session")
			{
				Result = activeSession
			};
		}

		UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("No active session found, refreshing local KeyPair"));

		// refresh keypair to make sure we have no conflicts with existing sessions
		auto newKeyPair = GetOrCreateSigningKeyPair(entityId, refresh: true);

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

		auto beamResultModel = new BeamResult<BeamSession>();

		UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Started polling for Session creation result"));
		// start polling for results of the operation
		auto error = false;

		auto pollingResult = await PollForResult(
			actionToPerform: () = > SessionsApi.GetSessionRequestAsync(beamSessionRequest.Id, cancellationToken),
			shouldRetry: res = > res.Status == GetSessionRequestResponse.StatusEnum.Pending,
			secondsTimeout: secondsTimeout,
			secondsBetweenPolls : 1,
			cancellationToken : cancellationToken);

		if (pollingResult == null)
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
			if (beamSession != null)
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
	}

	/// Opens an external browser to sign a transaction, returns the result via callback arg.
	///  @param[in]		entityId		Entity Id of the User performing signing
	///  @param[in]		operationId		Id of the Operation to sign. Returned by Beam API.
	///  @param[in]		chainId		ChainId to perform operation on. Defaults to 13337.
	///  @param[in]		signingBy		If set to Auto, will try to use a local Session and open Browser if there is no valid Session.
	///  @param[in]		secondsTimeout		Optional timeout in seconds, defaults to 240
	///  @param[in]		cancellationToken		Optional CancellationToken
	/// @return UniTask
	//async UniTask<BeamResult<CommonOperationResponse.StatusEnum>> SignOperationAsync(
	async UniTask<BeamResult<CommonOperationResponse.StatusEnum>> SignOperationAsync(
		FString entityId,
		FString operationId,
		int chainId = FBeamConstants::DefaultChainId,
		OperationSigningBy signingBy = OperationSigningBy.Auto,
		int secondsTimeout = DefaultTimeoutInSeconds,
		CancellationToken cancellationToken = default)
	{
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

			auto hasActiveSession = activeSessionKeyPair != null && activeSession != null;
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
	}
#endif // UN/PARTIALY PORTED C# CODE

	/// Clears any details of local Session like private key, or Session validity details. Useful when f.e. switching users on the same device.
	///  @param[in]		entityId		EntityId
	void ClearLocalSession(FString EntityId)
	{
		if (Storage)
		{
			Storage->Delete(FBeamConstants::Storage::BeamSession + EntityId);
			Storage->Delete(FBeamConstants::Storage::BeamSigningKey + EntityId);
		}
	}


private:

// TODO: Finish porting C# to Unreal C++
#if 0 // UN/PARTIALY PORTED C# CODE

	//async UniTask<BeamResult<CommonOperationResponse.StatusEnum>> SignOperationUsingBrowserAsync(
	async UniTask<BeamResult<CommonOperationResponse.StatusEnum>> SignOperationUsingBrowserAsync(
		CommonOperationResponse operation,
		int secondsTimeout,
		CancellationToken cancellationToken = default)
	{
		const FString& url = operation.Url;
		UE_CLOG(DebugLog, LogBeamClient, Log, TEXT("Opening %s..."), *url);

		// open identity.onbeam.com, give it operation id
		Application.OpenURL(url);

		// start polling for results of the operation
		FDateTime now = FDateTime::Now();
		//var now = DateTimeOffset.Now;
		auto pollingResult = await PollForResult(
			actionToPerform: () = > OperationApi.GetOperationAsync(operation.Id, cancellationToken),
			shouldRetry: res = > res == null ||
			res.Status != CommonOperationResponse.StatusEnum.Pending ||
			res.Status == CommonOperationResponse.StatusEnum.Pending &&
			res.UpdatedAt != null && res.UpdatedAt > now,
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
	}

	//async UniTask<BeamResult<CommonOperationResponse.StatusEnum>> SignOperationUsingSessionAsync(
	async UniTask<BeamResult<CommonOperationResponse.StatusEnum>> SignOperationUsingSessionAsync(
		CommonOperationResponse operation,
		KeyPair activeSessionKeyPair,
		CancellationToken cancellationToken = default)
	{
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
	}

	/// Will retry or return null if received 404.
	static async UniTask<T> PollForResult<T>(
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
					return null;
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

		return null;
	}

	async UniTask<(BeamSession, KeyPair)> GetActiveSessionAndKeysAsync(
		FString entityId,
		int chainId,
		CancellationToken cancellationToken = default)
	{
		BeamSession beamSession = null;
		auto sessionInfo = Storage.Get(FBeamConstants::Storage::BeamSession + entityId);
		if (sessionInfo != null)
		{
			beamSession = JsonConvert.DeserializeObject<BeamSession>(sessionInfo);
		}

		auto keyPair = GetOrCreateSigningKeyPair(entityId);

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
		return (null, keyPair);
	}

	KeyPair GetOrCreateSigningKeyPair(FString entityId, bool refresh = false)
	{
		if (!refresh)
		{
			auto privateKey = Storage.Get(FBeamConstants::Storage::BeamSigningKey + entityId);
			if (privateKey != null)
			{
				return KeyPair.Load(privateKey);
			}
		}

		auto newKeyPair = KeyPair.Generate();
		Storage.Set(FBeamConstants::Storage::BeamSigningKey + entityId, newKeyPair.PrivateHex);

		return newKeyPair;
	}

	Configuration GetConfiguration()
	{
		auto config = new Configuration
		{
			BasePath = BeamApiUrl,
		};
		config.ApiKey.Add("x-api-key", BeamApiKey);
		config.DefaultHeaders.Add("x-beam-sdk", "unreal");
		return config;
	}
#endif // UN/PARTIALY PORTED C# CODE



private:
	FString BeamApiKey;
	FString BeamApiUrl;
	bool DebugLog = false;
	IBeamStorageInterface* Storage = nullptr; //= new UBeamSaveGameStorage();
};
