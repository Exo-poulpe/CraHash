#include "MD5.h"


MD5::MD5()
{

}

MD5::MD5(std::string text)
{
	this->_text = text;
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

std::string MD5::hash()
{
	std::string text = this->_text;
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

std::string MD5::info(std::string text)
{
	std::string result = "Text : \"" + text + "\" MD5 : ";
	return result;
}

std::string MD5::Name()
{
	std::string result = "MD5";
	return result;
}