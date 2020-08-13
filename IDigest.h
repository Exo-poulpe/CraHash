#pragma once

#include <string>

class IDigest {
public:
	std::string hash(std::string text);
};