#pragma once

#include <string>
#include <vector>

#include "IDigest.h"

#include "include/CryptoPP/base64.h"
#include "include/CryptoPP/sha.h"
#include "include/CryptoPP/hex.h"

class SHA1 : public IDigest
{
public:
	SHA1();
	SHA1(std::string text);
	std::string hash(std::string text);
	std::string hash();
	std::string info(std::string text);
	std::string Name();
	static const int LENGTH = 40;

private:
	std::string _text;
	std::string ToLower(std::string text);
};

