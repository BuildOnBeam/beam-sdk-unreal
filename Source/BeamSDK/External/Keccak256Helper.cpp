#include "Keccak256Helper.h"
#include "HexConverter.h"
#include "Keccak256.h"
#include <algorithm>


std::string Keccak256Helper::ChecksumEncode(std::string addr)
{
	// address must be lowercase or hashedAddress will be incorrect
	std::transform(addr.begin(), addr.end(), addr.begin(),
		[](unsigned char c) { return std::tolower(c); });

	const auto hexAddrCStr = (unsigned char*)addr.c_str();
	uint8_t hashedAddress[32] = { 0 };
	Keccak256::getHash(&hexAddrCStr[0], 40, hashedAddress);
	const std::string hashedPubKeyHexString = HexConverter::ToHexString(hashedAddress, 32);

	std::string checksummedPubKeyHexString;
	for (auto nibbleIndex = 0; nibbleIndex < addr.length(); ++nibbleIndex)
	{
		if (std::isdigit(addr[nibbleIndex]))
		{
			checksummedPubKeyHexString.push_back(addr[nibbleIndex]);
		}
		else
		{
			auto nibble = hashedPubKeyHexString[nibbleIndex];
			const char div = '7';
			if (nibble > div)
			{
				checksummedPubKeyHexString.push_back(std::toupper(addr[nibbleIndex]));
			}
			else
			{
				checksummedPubKeyHexString.push_back(std::tolower(addr[nibbleIndex]));
			}
		}
	}
	return checksummedPubKeyHexString;
}

void Keccak256Helper::HashMessage(std::string messageHex, unsigned char hash[32])
{
	std::vector<unsigned char> messageBytesVector = HexConverter::FromHexString(messageHex);
	std::string msgSizeStr = std::to_string(messageBytesVector.size());

	std::string msgFirtChar = "\x19";
	std::string msgPrefix = msgFirtChar + "Ethereum Signed Message:\n" + std::to_string(messageBytesVector.size());
	int msgPrefixLength = msgPrefix.length();
	const char* msgPrefixBytes = msgPrefix.c_str();

	const int msgSize = msgPrefixLength + messageBytesVector.size();
	uint8_t* bytes = new uint8_t[msgSize];

	std::copy(msgPrefixBytes, msgPrefixBytes + msgPrefixLength, bytes);
	std::copy(messageBytesVector.begin(), messageBytesVector.end(), bytes + msgPrefixLength);

	Keccak256::getHash(bytes, msgSize, hash);
}


///// EIP-712 Signing /////


std::vector<uint8_t> Keccak256Helper::keccak256(const std::vector<uint8_t>& data)
{
    std::vector<uint8_t> hash(32); // 32 bytes for Keccak-256
    //sha3_256(data.data(), data.size(), hash.data());

	Keccak256::getHash(data.data(), data.size(), hash.data());
	return hash;
}

std::vector<uint8_t> Keccak256Helper::keccak256(const std::string& stringtoHash)
{
    std::vector<uint8_t> hashBytes(stringtoHash.begin(), stringtoHash.end());
	return keccak256(hashBytes);
}


std::vector<uint8_t> Keccak256Helper::createDigest(const std::vector<uint8_t>& domainHash, const std::vector<uint8_t>& dataHash)
{
    std::vector<uint8_t> prefix = {0x19, 0x01}; // Standard EIP-712 prefix
    std::vector<uint8_t> digest = prefix;
    digest.insert(digest.end(), domainHash.begin(), domainHash.end());
    digest.insert(digest.end(), dataHash.begin(), dataHash.end());
    return keccak256(digest);
}

std::vector<uint8_t> Keccak256Helper::signDigest(const std::vector<uint8_t>& digest, const std::vector<uint8_t>& privateKey)
{
    secp256k1_context* ctx = secp256k1_context_create(SECP256K1_CONTEXT_SIGN);
    secp256k1_ecdsa_signature signature;

    secp256k1_ecdsa_sign(ctx, &signature, digest.data(), privateKey.data(), nullptr, nullptr);

    std::vector<uint8_t> signatureData(64); // 64 bytes for the signature
    secp256k1_ecdsa_signature_serialize_compact(ctx, signatureData.data(), &signature);

    secp256k1_context_destroy(ctx);
    return signatureData;
}
