#pragma once

#include <string>
#include <vector>

class IDigest {
public:
	virtual std::string hash(std::string text) = 0;
	virtual std::string hash() = 0;
	virtual std::string info(std::string text) = 0;
	virtual std::string Name() = 0;
};