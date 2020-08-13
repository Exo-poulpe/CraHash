#include "MD5.h"


MD5::MD5()
{
	
}

std::string MD5::ToLower(std::string text)
{
	std::string result;
	result.resize(text.size());
	for (int i = 0; i < text.size(); i++)
	{
		result.at(i) = std::tolower(text.at(i));
	}
	return result;
}

std::string MD5::hash(std::string text)
{
	std::string result;
	CryptoPP::byte temp[CryptoPP::MD5::DIGESTSIZE];
	CryptoPP::HexEncoder encoder;

	CryptoPP::MD5 hash;

	hash.CalculateDigest(temp, (CryptoPP::byte*)text.c_str(), text.size());


	encoder.Attach(new CryptoPP::StringSink(result));
	encoder.Put(temp, sizeof(temp));
	encoder.MessageEnd();


	return ToLower(result);
}
