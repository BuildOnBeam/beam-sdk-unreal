#pragma once
#include <string>
#include "secp256k1.h"

class BEAMSDK_API KeyPair
{
private:

	unsigned char seckey[32];
	secp256k1_pubkey pubkey;
	bool isInitialized = false;

public:

	bool Generate();
	bool Initialize(std::string seckeyHex);
	bool IsSet() const;
	std::string GetPrivateKeyHex();
	std::string GetPublicKeyHex();
	std::string GetAddress();
	std::string Sign(std::string messageHex);
	std::string SignMarketplaceTransactionHash(std::string hashString);
};
