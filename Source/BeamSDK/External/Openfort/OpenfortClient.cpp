#include "OpenfortClient.h"

bool UOpenfortClient::GenerateSessionKey()
{
	return keyPair.Generate();
}

bool UOpenfortClient::InitializeSessionKey(const FString& secKeyHex)
{
	return keyPair.Initialize(std::string(TCHAR_TO_UTF8(*secKeyHex)));
}

FString UOpenfortClient::GetSessionPublicKeyHex()
{
	return keyPair.GetPublicKeyHex().c_str();
}

FString UOpenfortClient::GetSessionPrivateKeyHex()
{
	return keyPair.GetPrivateKeyHex().c_str();
}

FString UOpenfortClient::GetSessionKeyAddress()
{
	return keyPair.GetAddress().c_str();
}

void UOpenfortClient::SetApiKey(const FString& apiKey)
{
	API_KEY = apiKey;
}

FString UOpenfortClient::SignMessage(const FString& message)
{
	return keyPair.Sign(std::string(TCHAR_TO_UTF8(*message))).c_str();
}

void UOpenfortClient::SignatureSession(const FString& session, const FString& signature)
{
	ApiClient client = ApiClient(API_KEY);
	client.SignatureSession(session, signature, OnSignatureSessionComplete);
}

void UOpenfortClient::SignatureTransactionIntent(const FString& transactionIntentId, const FString& signature)
{
	ApiClient client = ApiClient(API_KEY);
	client.SignatureTransactionIntent(transactionIntentId, signature, OnSignatureTransactionIntentComplete);
}
