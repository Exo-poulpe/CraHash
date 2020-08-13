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
	std::string hash(std::string text);

private:
	
};

