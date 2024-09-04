#pragma once

#include <string>
#include "secp256k1.h"  // For ECDSA operations
#include "uint256_t.h"

// EIP-712 domain separator structure
struct EIP712Domain;
struct MyTypedData;

class Keccak256Helper
{
public:
	static std::string ChecksumEncode(std::string addr);
	static void HashMessage(std::string messageHex, unsigned char hash[32]);

public:
	static std::vector<uint8_t> keccak256(const std::vector<uint8_t>& data);
	static std::vector<uint8_t> keccak256(const std::string& stringtoHash);
	static std::vector<uint8_t> hashDomain(const EIP712Domain& domain);
	static std::vector<uint8_t> hashTypedData(const MyTypedData& data);
	static std::vector<uint8_t> createDigest(const std::vector<uint8_t>& domainHash, const std::vector<uint8_t>& dataHash);
	static std::vector<uint8_t> signDigest(const std::vector<uint8_t>& digest, const std::vector<uint8_t>& privateKey);
};

// EIP-712 domain separator structure
struct EIP712Domain
{
	std::string name;
	std::string version;
    uint256_t chainId;
	std::string verifyingContract;
};

// Example data structure (replace with your specific structure)
struct MyTypedData
{
	std::string field1;
	uint256_t field2;
};
