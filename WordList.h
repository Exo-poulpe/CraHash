#pragma once

#include <string>
#include <chrono>

#include "IDigest.h"

class WordList
{
private:
	std::string _filePath;
	IDigest* _digest;
	bool _verbose = false;
	bool _counter = false;
	bool _timer = true;
	unsigned int counter = 0;

public:
	WordList(std::string filePath, IDigest* digest, bool verbose = false, bool counter = false, bool timer = true);
	std::string Crack(std::string);
};

