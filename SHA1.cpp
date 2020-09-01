#include "SHA1.h"

SHA1::SHA1()
{

}

SHA1::SHA1(std::string text)
{
	this->_text = text;
}

std::string SHA1::ToLower(std::string text)
{
	std::string result;
	result.resize(text.size());
	for (int i = 0; i < text.size(); i++)
	{
		result.at(i) = std::tolower(text.at(i));
	}
	return result;
}

std::string SHA1::hash(std::string text)
{
	std::string result;
	CryptoPP::byte temp[CryptoPP::SHA1::DIGESTSIZE];
	CryptoPP::HexEncoder encoder;

	CryptoPP::SHA1 hash;

	hash.CalculateDigest(temp, (CryptoPP::byte*)text.c_str(), text.size());


	encoder.Attach(new CryptoPP::StringSink(result));
	encoder.Put(temp, sizeof(temp));
	encoder.MessageEnd();


	return ToLower(result);
}

std::string SHA1::hash()
{
	std::string text = this->_text;
	std::string result = hash(this->_text);

	return ToLower(result);
}

std::string SHA1::info(std::string text)
{
	std::string result = "Text : \"" + text + "\" SHA1 : ";
	return result;
}

std::string SHA1::Name()
{
	std::string result = "SHA1";
	return result;
}