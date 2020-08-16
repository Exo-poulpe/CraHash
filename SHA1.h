#pragma once

#include <string>

#include "IDigest.h"

#include "include/CryptoPP/base64.h"
#include "include/CryptoPP/md5.h"
#include "include/CryptoPP/hex.h"

class SHA1
{
public:
	SHA1();
	SHA1(std::string text);
	std::string hash(std::string text);
	std::string hash();

private:
	std::string _text;
	std::string ToLower(std::string text);
};

