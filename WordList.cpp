#include "WordList.h"

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>

WordList::WordList(std::string filePath, IDigest* digest, bool verbose, bool counter, bool timer)
{
	this->_filePath = filePath;
	this->_digest = digest;
	this->_verbose = verbose;
	this->_counter = counter;
	this->_timer = timer;
}

std::string WordList::Crack(std::string hash)
{
	typedef std::chrono::high_resolution_clock Time;
	typedef std::chrono::duration<float> fsec;
	std::chrono::time_point<std::chrono::steady_clock> start = Time::now();

	std::ifstream input(this->_filePath);
	std::string line;
	while (!input.eof())
	{
		std::getline(input, line);
		std::string tmp = this->_digest->hash(line);
		counter += 1;
		if (this->_verbose)
		{
			std::cout << "Password tested : " << line << " :::" << tmp << std::endl;
		}
		if (tmp == hash)
		{
			if (this->_timer)
			{
				std::chrono::time_point<std::chrono::steady_clock> stop = Time::now();
				fsec fs = (stop - start);
				std::cout << "Time elapsed : " << fs.count() << " s" << std::endl;
			}
			if (this->_counter)
			{
				std::cout << "Password number : " << this->counter << std::endl;
			}
			input.close();
			return line;
		}
	}
	input.close();
	if (this->_timer)
	{
		std::chrono::time_point<std::chrono::steady_clock> stop = Time::now();
		fsec fs = (stop - start);
		std::cout << "Time elapsed : " << fs.count() << " s" << std::endl;
	}
	if (this->_counter)
	{
		std::cout << "Password number : " << this->counter << std::endl;
	}
	return hash;

}