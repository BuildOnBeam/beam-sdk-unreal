#pragma once

#include "CoreMinimal.h"
#include "Async/Future.h"
//#include "Experimental/Async/AwaitableTask.h"
//#include "Experimental/Coroutine/Coroutine.h"
//#include "Experimental/Coroutine/CoroEvent.h"

// Openfort
#include "KeyPair.h"

// Player Client
#include "BeamPlayerClientAPI.h"

// Beam SDK
#include "BeamApiError.h"
#include "BeamConstants.h"
#include "BeamEnvironment.h"
#include "BeamResult.h"
#include "BeamSession.h"
#include "BeamStorageInterface.h"
#include "BeamOperationSigningBy.h"

#include "Async/Async.h"
#include "Engine/TimerHandle.h"

#include "BeamClient.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogBeamClient, Log, All);

constexpr int DefaultTimeoutInSeconds = 240;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class BEAMSDK_API UBeamClient : public UObject
{
	GENERATED_BODY()

protected:
	template<typename TTargetApi>
	TSharedPtr<TTargetApi>& ConfigureApi(TSharedPtr<TTargetApi>& targetApi)
	{
		targetApi->SetURL(BeamApiUrl);
		targetApi->AddHeaderParam(FBeamConstants::BeamAPIKeyHeader, BeamApiKey);
		targetApi->AddHeaderParam(FBeamConstants::BeamSDKHeader, FBeamConstants::BeamSDKUnreal);
		return targetApi;
	}

public:
	class FBeamCancellationToken
	{
	public:
		FBeamCancellationToken()
			: bCancel(false)
		{}

		bool ShouldCancel() { return bCancel.load(); }
		void Cancel() { bCancel.store(true); }
		void Reset() { bCancel.store(false); }

	private:
		std::atomic<bool> bCancel;
	};

public:
	TSharedPtr<PlayerClientAssetsApi> AssetsApi = MakeShared<PlayerClientAssetsApi>();
	TSharedPtr<PlayerClientExchangeApi> ExchangeApi = MakeShared<PlayerClientExchangeApi>();
	TSharedPtr<PlayerClientHealthApi> HealthApi = MakeShared<PlayerClientHealthApi>();
	TSharedPtr<PlayerClientMarketplaceApi> MarketplaceApi = MakeShared<PlayerClientMarketplaceApi>();
	TSharedPtr<PlayerClientSessionsApi> SessionsApi = MakeShared<PlayerClientSessionsApi>();
	TSharedPtr<PlayerClientTransactionsApi> TransactionsApi = MakeShared<PlayerClientTransactionsApi>();
	TSharedPtr<PlayerClientUsersApi> UsersApi = MakeShared<PlayerClientUsersApi>();
	TSharedPtr<PlayerClientOperationApi> OperationApi = MakeShared<PlayerClientOperationApi>();
	TSharedPtr<PlayerClientConnectorApi> ConnectorApi = MakeShared<PlayerClientConnectorApi>();

public:
	UBeamClient();


// Tests
public:
	UFUNCTION(BlueprintCallable, Category = "Test")
	void RunTests();


// Virtual methods
public:
	/// Launches a URL in a browser. (optionally override if needed)
	///  @param[in]		InUrl		The url to browse to.
	///  @param[in]		InParams	Optional input parameters.
	///  @param[out]	OutError	Error result from launch request.
	virtual void LaunchURL(const FString& InUrl, FString& InParams, FString& OutError);

	/// Launches a URL in a browser. (optionally override if needed)
	///  @param[in]		InUrl		The url to browse to.
	/// @return Error result from launch request.
	virtual FString LaunchURL(const FString& Url);

// Config
public:

	/// Sets Publishable Beam API key on the client. WARNING: Do not use keys other than Publishable, they're meant to be private, server-side only!
	///  @param[in]		PublishableApiKey	Publishable Beam API key
	/// @return BeamClient
	UBeamClient* SetBeamApiKey(const FString& PublishableApiKey);

	/// Sets Environment on the client.
	///  @param[in]		Environment		BeamEnvironment.Mainnet or BeamEnvironment.Testnet (defaults to Testnet)
	/// @return BeamClient
	UBeamClient* SetEnvironment(EBeamEnvironment Environment);

	/// Sets custom storage for Session related information. Defaults to UBeamSaveGameStorage.
	///  @param[in]		Storage		Storage that implements IStorage
	/// @return BeamClient
	UBeamClient* SetStorage(IBeamStorageInterface* storage);

	/// Set to true, to enable Debug.Log() statements. Defaults to false.
	///  @param[in]		enable		True to enable
	/// @return BeamClient
	UBeamClient* SetDebugLogging(bool enable);

public:

	/// Will connect given EntityId for your game to a User.
	/// This will also happen on first possible action signed by user in the browser.
	///  @param[in]		EntityId		Entity Id of the User performing signing
	///  @param[in]		ChainId			ChainId to perform operation on. Defaults to 13337.
	///  @param[in]		SecondsTimeout	Optional timeout in seconds, defaults to 240
	/// @return TFuture
	TFuture<TBeamResult<PlayerClientGetConnectionRequestResponse::StatusEnum>> ConnectUserToGameAsync(
		FString EntityId,
		int32 ChainId = FBeamConstants::DefaultChainId,
		int32 SecondsTimeout = DefaultTimeoutInSeconds
	);

	/// Retrieves active, valid session.
	///  @param[in]		entityId	Entity Id of the User performing signing
	///  @param[in]		chainId		ChainId to perform operation on. Defaults to 13337.
	/// @return TFuture
	TFuture<TBeamResult<FBeamSession>> GetActiveSessionAsync(
		FString entityId,
		int chainId = FBeamConstants::DefaultChainId
	);

	/// Revokes given Session Address. Always opens Browser as User has to sign it with his key.
	///  @param[in]		entityId		Entity Id of the User performing signing
	///  @param[in]		sessionAddress	address of a Session to revoke
	///  @param[in]		chainId			ChainId to perform operation on. Defaults to 13337.
	///  @param[in]		secondsTimeout	Optional timeout in seconds, defaults to 240
	/// @return TFuture
	TFuture<TBeamResult<PlayerClientCommonOperationResponse::StatusEnum>> RevokeSessionAsync(
		FString entityId,
		FString sessionAddress,
		int chainId = FBeamConstants::DefaultChainId,
		int secondsTimeout = DefaultTimeoutInSeconds
	);

	/// Opens an external browser to sign a Session, returns the result via callback arg.
	///  @param[in]		entityId		Entity Id of the User performing signing
	///  @param[in]		chainId			ChainId to perform operation on. Defaults to 13337.
	///  @param[in]		secondsTimeout	Optional timeout in seconds, defaults to 240
	/// @return TFuture
	TFuture<TBeamResult<FBeamSession>> CreateSessionAsync(
		FString entityId,
		int chainId = FBeamConstants::DefaultChainId,
		int secondsTimeout = DefaultTimeoutInSeconds
	);

	/// Opens an external browser to sign a transaction, returns the result via callback arg.
	///  @param[in]		entityId		Entity Id of the User performing signing
	///  @param[in]		operationId		Id of the Operation to sign. Returned by Beam API.
	///  @param[in]		chainId			ChainId to perform operation on. Defaults to 13337.
	///  @param[in]		signingBy		If set to Auto, will try to use a local Session and open Browser if there is no valid Session.
	///  @param[in]		secondsTimeout	Optional timeout in seconds, defaults to 240
	/// @return TFuture
	TFuture<TBeamResult<PlayerClientCommonOperationResponse::StatusEnum>> SignOperationAsync(
		FString entityId,
		FString operationId,
		int chainId = FBeamConstants::DefaultChainId,
		EBeamOperationSigningBy signingBy = EBeamOperationSigningBy::Auto,
		int secondsTimeout = DefaultTimeoutInSeconds
	);

	/// Clears any details of local Session like private key, or Session validity details. Useful when f.e. switching users on the same device.
	///  @param[in]		entityId		EntityId
	void ClearLocalSession(FString EntityId);

private:

	TFuture<TBeamResult<PlayerClientCommonOperationResponse::StatusEnum>> SignOperationUsingBrowserAsync(PlayerClientCommonOperationResponse operation, int secondsTimeout);

	TFuture<TBeamResult<PlayerClientCommonOperationResponse::StatusEnum>> SignOperationUsingSessionAsync(PlayerClientCommonOperationResponse operation, KeyPair activeSessionKeyPair);

	FTimerHandle PollTimerHandle;
	void PollForSessionCreation(PlayerClientSessionsApi::GetSessionRequestRequest Request);

	/// Will retry or return nullptr if received 404.
	template<typename TResultType>
	static TFuture<TOptional<TResultType>> PollForResult(
		TFunction<TFuture<TResultType>()> actionToPerform,
		TFunction<bool(const TResultType&)> shouldRetry,
		int secondsTimeout = DefaultTimeoutInSeconds,
		int secondsBetweenPolls = 1,
		TSharedPtr<FBeamCancellationToken> cancellationToken = nullptr
	)
	{
		const auto Promise = MakeShared<TPromise<TOptional<TResultType>>, ESPMode::ThreadSafe>();
		AsyncTask(ENamedThreads::AnyThread, [&, Promise, secondsTimeout, secondsBetweenPolls, actionToPerform, shouldRetry, cancellationToken]()
		{
			// This code will run asynchronously, without freezing the game thread
			FPlatformProcess::Sleep(2.0f);

			TOptional<TResultType> result;
			FDateTime endTime = FDateTime::Now() + FTimespan(0, 0, secondsTimeout);
			while ((endTime - FDateTime::Now()).GetTotalSeconds() > 0.0)
			{
				TFuture<TResultType> actionFuture = actionToPerform();
				while (!actionFuture.IsReady())
				{
					if (actionFuture.WaitFor(FTimespan::FromMilliseconds(100.0)))
					{
						result = actionFuture.Get();
						if (result.IsSet())
						{
							if (result.GetValue().GetHttpResponseCode() == 404)
							{
								result.Reset();
							}
						}
						break;
					}
					else if (cancellationToken.IsValid() && cancellationToken->ShouldCancel())
					{
						cancellationToken->Reset();
						result.Reset();
						break;
					}
				}

				if (result.IsSet())
				{
					auto temp = result.GetValue();
					bool test = shouldRetry(temp);
					if (!test)
					{
						break;
					}
				}

				FPlatformProcess::Sleep(secondsBetweenPolls);
			}

			AsyncTask(ENamedThreads::GameThread, [Promise, result]()
			{
				// This code will be executed on the game thread
				Promise->SetValue(result);
			});
		});
		return Promise->GetFuture();
	}

	TFuture<FBeamSessionAndKeyPair> GetActiveSessionAndKeysAsync(
		FString entityId,
		int chainId
	);

public:
	void GetOrCreateSigningKeyPair(KeyPair& OutKeyPair, FString InEntityId, bool InRefresh = false);

private:
	FString BeamApiKey;
	FString BeamApiUrl;
	bool DebugLog = false;
	IBeamStorageInterface* Storage = nullptr; //= new UBeamSaveGameStorage();
};
