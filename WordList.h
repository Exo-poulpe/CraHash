#pragma once

#include <string>
#include <chrono>

#include "IDigest.h"
#include "Crackable.h"

#include "boost/thread/thread.hpp"


class WordList
{
private:
	std::string _filePath;
	IDigest* _digest;
	bool _verbose = false;
	bool _counter = false;
	bool _timer = true;
	unsigned int counter = 0;
	std::string ToLower(std::string text);
	std::string iso_latin_1_to_utf8(std::string text);

public:
	WordList(std::string filePath, IDigest* digest, bool verbose = false, bool counter = false, bool timer = true);
	std::string Crack(std::string);
};

