#pragma once
#include <string>
#include <vector>

class BEAMSDK_API HexConverter
{
public:
	static std::string ToHexString(unsigned char data[], int len);
	static std::vector<unsigned char> FromHexString(std::string);
};