#pragma once

#include <string>

#include "IDigest.h"

#include "include/CryptoPP/base64.h"
#include "include/CryptoPP/hex.h"


class NTLM : public IDigest
{
public:
	NTLM();
	NTLM(std::string text);
	std::string hash(std::string text);
	std::string hash();
	std::string info(std::string text);
	std::string Name();
	static const int LENGTH = 32;

private:
	std::string _text;
	std::string ToLower(std::string text);
	const char* charset = std::string("abcdefghijklmnopqrstuvwxyz0123456789\0").c_str();
};