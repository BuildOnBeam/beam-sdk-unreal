#pragma once

#include "CoreMinimal.h"
#include "Async/Future.h"

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

#include "BeamClient.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogBeamClient, Log, All);

typedef PlayerClientConfirmOperationRequestTransactionsInner ConfirmOperationRequestAction;

typedef PlayerClientPlayerOperationResponse PlayerOperationResponse;
typedef PlayerClientPlayerOperationAction PlayerOperationResponseAction;
typedef PlayerClientConfirmOperationRequest ConfirmOperationRequest;
typedef PlayerClientCreateConnectionRequestResponse CreateConnectionRequestResponse;
typedef PlayerClientGenerateSessionRequestResponse GenerateSessionRequestResponse;
typedef PlayerClientGetAssetListingsResponseDataInner GetAssetListingsResponseDataInner;
typedef PlayerClientGetConnectionRequestResponse GetConnectionRequestResponse;
typedef PlayerClientGetSessionRequestResponse GetSessionRequestResponse;
typedef PlayerClientOperationApi::GetOperationResponse GetOperationResponse;

// Note: use with ::EnumFromString(StatusEnum) on the response types above.
typedef PlayerClientPlayerOperationResponse::StatusEnum PlayerOperationStatusEnum;
typedef PlayerClientPlayerOperationAction::TypeEnum
PlayerOperationResponseActionTypeEnum;
typedef PlayerClientConfirmOperationRequest::StatusEnum ConfirmOperationStatusEnum;
typedef PlayerClientCreateConnectionRequestResponse::StatusEnum CreateConnectionRequestStatusEnum;
typedef PlayerClientGenerateSessionRequestResponse::StatusEnum GenerateSessionRequestStatusEnum;
typedef PlayerClientGetAssetListingsResponseDataInner::StatusEnum GetAssetListingsStatusEnum;
typedef PlayerClientGetConnectionRequestResponse::StatusEnum GetConnectionRequestStatusEnum;
typedef PlayerClientGetSessionRequestResponse::StatusEnum GetSessionRequestStatusEnum;

typedef TBeamResult<FBeamSession> BeamSessionResult;
typedef TBeamResult<PlayerOperationStatusEnum> BeamOperationResult;
typedef TBeamResult<GetConnectionRequestStatusEnum> BeamConnectionResult;


/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class BEAMSDK_API UBeamClient : public UObject
{
	GENERATED_BODY()

protected:
	template <typename TTargetApi>
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
		{
		}

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
	TSharedPtr<PlayerClientRampApi> RampApi = MakeShared<PlayerClientRampApi>();

public:
	UBeamClient();


	// Virtual methods
public:
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
	///  @param[in]		entityId		Entity Id of the User performing signing
	///  @param[in]		chainId			ChainId to perform operation on. Defaults to 13337.
	///  @param[in]		secondsTimeout	Optional timeout in seconds, defaults to 240
	///  @param[in]		authProvider    Optional authProvider, if set to Any(default), User will be able to choose social login provider. Useful if you want to present Google/Discord/Apple/etc options within your UI.
	/// @return TFuture
	TFuture<BeamConnectionResult> ConnectUserToGameAsync(
		FString entityId,
		int32 chainId = FBeamConstants::DefaultChainId,
		int32 secondsTimeout = FBeamConstants::DefaultTimeoutInSeconds,
		TOptional<PlayerClientCreateConnectionRequestInput::AuthProviderEnum> authProvider =
			PlayerClientCreateConnectionRequestInput::AuthProviderEnum::Any,
		TSharedPtr<FBeamCancellationToken>* OutCancellationToken = nullptr
	);

	/// Retrieves active, valid session.
	///  @param[in]		entityId	Entity Id of the User performing signing
	///  @param[in]		chainId		ChainId to perform operation on. Defaults to 13337.
	/// @return TFuture
	TFuture<BeamSessionResult> GetActiveSessionAsync(
		FString entityId,
		int chainId = FBeamConstants::DefaultChainId,
		TSharedPtr<FBeamCancellationToken>* OutCancellationToken = nullptr
	);

	/// Revokes given Session Address. Always opens Browser as User has to sign it with his key.
	///  @param[in]		entityId		Entity Id of the User performing signing
	///  @param[in]		sessionAddress	address of a Session to revoke
	///  @param[in]		chainId			ChainId to perform operation on. Defaults to 13337.
	///  @param[in]		secondsTimeout	Optional timeout in seconds, defaults to 240
	///  @param[in]		authProvider    Optional authProvider, if set to Any(default), User will be able to choose social login provider. Useful if you want to present Google/Discord/Apple/etc options within your UI.
	/// @return TFuture
	TFuture<BeamOperationResult> RevokeSessionAsync(
		FString entityId,
		FString sessionAddress,
		int chainId = FBeamConstants::DefaultChainId,
		int secondsTimeout = FBeamConstants::DefaultTimeoutInSeconds,
		TOptional<PlayerClientRevokeSessionRequestInput::AuthProviderEnum> authProvider =
			PlayerClientRevokeSessionRequestInput::AuthProviderEnum::Any,
		TSharedPtr<FBeamCancellationToken>* OutCancellationToken = nullptr
	);

public:
	/// Opens an external browser to sign a Session, returns the result via callback arg.
	///  @param[in]		entityId		Entity Id of the User performing signing
	///  @param[in]		chainId			ChainId to perform operation on. Defaults to 13337.
	///  @param[in]		secondsTimeout	Optional timeout in seconds, defaults to 240
	///  @param[in]     suggestedExpiry Suggested Expiry date that will be pre-selected for the User
	///  @param[in]		authProvider    Optional authProvider, if set to Any(default), User will be able to choose social login provider. Useful if you want to present Google/Discord/Apple/etc options within your UI.
	/// @return TFuture
	TFuture<BeamSessionResult> CreateSessionAsync(
		FString entityId,
		int chainId = FBeamConstants::DefaultChainId,
		int secondsTimeout = FBeamConstants::DefaultTimeoutInSeconds,
		TOptional<FDateTime> suggestedExpiry = TOptional<FDateTime>(),
		TOptional<PlayerClientGenerateSessionUrlRequestInput::AuthProviderEnum> authProvider =
			PlayerClientGenerateSessionUrlRequestInput::AuthProviderEnum::Any,
		TSharedPtr<FBeamCancellationToken>* OutCancellationToken = nullptr
	);

	/// Opens an external browser to sign a transaction, returns the result via callback arg.
	///  @param[in]		entityId		Entity Id of the User performing signing
	///  @param[in]		operationId		Id of the Operation to sign. Returned by Beam API.
	///  @param[in]		chainId			ChainId to perform operation on. Defaults to 13337.
	///  @param[in]		signingBy		If set to Auto, will try to use a local Session and open Browser if there is no valid Session.
	///  @param[in]		secondsTimeout	Optional timeout in seconds, defaults to 240
	/// @return TFuture
	TFuture<BeamOperationResult> SignOperationAsync(
		FString entityId,
		FString operationId,
		int chainId = FBeamConstants::DefaultChainId,
		EBeamOperationSigningBy signingBy = EBeamOperationSigningBy::Auto,
		int secondsTimeout = FBeamConstants::DefaultTimeoutInSeconds,
		TSharedPtr<FBeamCancellationToken>* OutCancellationToken = nullptr
	);

	/// Clears any details of local Session like private key, or Session validity details. Useful when f.e. switching users on the same device.
	///  @param[in]		entityId		EntityId
	void ClearLocalSession(FString entityId);

private:
	TFuture<BeamOperationResult> SignOperationUsingBrowserAsync(PlayerOperationResponse operation, int secondsTimeout,
	                                                            TSharedPtr<FBeamCancellationToken>* OutCancellationToken
		                                                            = nullptr);

	TFuture<BeamOperationResult> SignOperationUsingSessionAsync(PlayerOperationResponse operation,
	                                                            KeyPair activeSessionKeyPair,
	                                                            TSharedPtr<FBeamCancellationToken>* OutCancellationToken
		                                                            = nullptr);

	/// Will retry or return nullptr if received 404.
	template <typename TResultType>
	static TFuture<TOptional<TResultType>> PollForResult(
		TFunction<TFuture<TResultType>()> actionToPerform,
		TFunction<bool(const TResultType&)> shouldRetry,
		int secondsTimeout = FBeamConstants::DefaultTimeoutInSeconds,
		int secondsBetweenPolls = 1,
		TSharedPtr<FBeamCancellationToken> cancellationToken = nullptr
	)
	{
		const auto Promise = MakeShared<TPromise<TOptional<TResultType>>, ESPMode::ThreadSafe>();
		AsyncTask(ENamedThreads::AnyThread,
		          [&, Promise, secondsTimeout, secondsBetweenPolls, actionToPerform, shouldRetry, cancellationToken]()
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

	TFuture<FBeamSessionAndKeyPair> GetActiveSessionAndKeysAsync(FString entityId, int chainId);

public:
	void GetOrCreateSigningKeyPair(KeyPair& OutKeyPair, FString InEntityId, bool InRefresh = false);

private:
	FString BeamApiKey;
	FString BeamApiUrl;
	bool DebugLog = false;
	IBeamStorageInterface* Storage = nullptr;
};
