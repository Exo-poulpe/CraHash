#pragma once

#include <string>

#include "IDigest.h"

#include "include/CryptoPP/base64.h"
#include "include/CryptoPP/md5.h"
#include "include/CryptoPP/hex.h"

class MD5 : public IDigest
{
public:
	MD5();
	MD5(std::string text);
	std::string hash(std::string text);
	std::string hash();
	std::string info(std::string text);
	static const int LENGTH = 32;

private:
	std::string _text;
	std::string ToLower(std::string text);
};

