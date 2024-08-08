#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KeyPair.h"
#include "ApiClient.h"
#include "Entities.h"
#include "OpenfortClient.generated.h"

class UOpenfortClient;
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FSignatureSessionComplete, UOpenfortClient, OnSignatureSessionComplete, FSignatureSessionResponse, Response);

class UOpenfortClient;
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FSignatureTransactionIntentComplete, UOpenfortClient, OnSignatureSessionComplete, FTransactionIntentResponse, Response);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UOpenfortClient : public UObject
{
	GENERATED_BODY()

private:
	FString API_KEY;

	ApiClient apiClient;

	ApiClient GetApiClient();

	KeyPair keyPair;

public:	
	UFUNCTION(BlueprintCallable)
	void SetApiKey(const FString& apiKey);		

	/** Generates a new key pair */
	UFUNCTION(BlueprintCallable, Category = "Session")
	bool GenerateSessionKey();		

	/** Generates a new key pair */
	UFUNCTION(BlueprintCallable, Category = "Session")
	bool InitializeSessionKey(const FString& privateKey);

	UFUNCTION(BlueprintCallable, Category = "Session")
	FString GetSessionPublicKeyHex();

	UFUNCTION(BlueprintCallable, Category = "Session")
	FString GetSessionPrivateKeyHex();

	UFUNCTION(BlueprintCallable, Category = "Session")
	FString GetSessionKeyAddress();

	UFUNCTION(BlueprintCallable, Category = "Session")
	FString SignMessage(const FString& message);		

	/** Sends a request to session signature endpoint */
	UFUNCTION(BlueprintCallable, Category = "Api")
	void SignatureSession(const FString& session, const FString& signature); 

	/** Sends a request to session signature endpoint */
	UFUNCTION(BlueprintCallable, Category = "Api")
	void SignatureTransactionIntent(const FString& transactionIntentId, const FString& signature); 
	
	UPROPERTY(BlueprintAssignable)
    FSignatureSessionComplete OnSignatureSessionComplete;
	
	UPROPERTY(BlueprintAssignable)
    FSignatureTransactionIntentComplete OnSignatureTransactionIntentComplete;
};
