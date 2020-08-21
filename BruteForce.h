#pragma once

#include <string>
#include <chrono>

#include "IDigest.h"

#include "include/CryptoPP/base64.h"
#include "include/CryptoPP/hex.h"
#include "include/CryptoPP/md5.h"

class BruteForce
{
private:
	using Minutes = std::chrono::duration<int,int>;
	using Seconds = std::chrono::duration<int,int>;
	std::string ToLower(std::string text);
	std::string ToLowerToHex(std::string text);
	std::string CheckPassWordLetter(std::string pass);
	char NewCharFromChar(char letter);
	std::vector<char> Alphabet;
	unsigned int countPassword = 0;

public:
	std::string ALPHABET = "abcdefghijklmnopqrstuvwxyz";
	std::string ALPHABET_UPPER = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string ALPHABET_UPPER_NUMBER = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	std::string ALPHABET_UPPER_NUMBER_SPECIAL = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,-_)(/&%ç* \"!";
	BruteForce();
	std::string BruteForcing(std::string hash, IDigest* mode, std::string alpa, bool verbose = false,bool counter = false,bool timer = true);
};

