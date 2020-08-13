#pragma once

#include <string>

class IDigest {
public:
	virtual std::string hash(std::string text) = 0;
};