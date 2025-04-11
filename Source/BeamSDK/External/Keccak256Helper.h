#pragma once

#include <string>
#include <vector>
#include "secp256k1.h"  // For ECDSA operations

class Keccak256Helper
{
public:
	static std::string ChecksumEncode(std::string addr);
	static void HashMessage(std::string messageHex, unsigned char hash[32]);

public:
	static std::vector<uint8_t> keccak256(const std::vector<uint8_t>& data);
	static std::vector<uint8_t> keccak256(const std::string& stringtoHash);
	static std::vector<uint8_t> createDigest(const std::vector<uint8_t>& domainHash, const std::vector<uint8_t>& dataHash);
	static std::vector<uint8_t> signDigest(const std::vector<uint8_t>& digest, const std::vector<uint8_t>& privateKey);
};
