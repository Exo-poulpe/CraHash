#pragma once

#include <string>

#include "IDigest.h"

#include "include/CryptoPP/base64.h"
#include "include/CryptoPP/md5.h"

class BruteForce
{
private:
	const char* ALPHABET = "abcdefghijklmnopqrstuvwxyz";
	const char* ALPHABET_UPPER = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const char* ALPHABET_UPPER_NUMBER = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	std::string ToLower(std::string text);

public:
};

