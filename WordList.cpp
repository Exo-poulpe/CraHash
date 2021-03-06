#include "WordList.h"

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>

#include <locale>

WordList::WordList(std::string filePath, IDigest* digest, bool verbose, bool counter, bool timer)
{
	this->_filePath = filePath;
	this->_digest = digest;
	this->_verbose = verbose;
	this->_counter = counter;
	this->_timer = timer;
}

std::string WordList::ToLower(std::string text)
{
	std::string result;
	result.resize(text.size());
	for (int i = 0; i < text.size(); i++)
	{
		result.at(i) = std::tolower(text.at(i));
	}
	return result;
}

std::string WordList::Crack(std::string hash)
{
	KeyEventCapture::keyPressed = false;
	boost::thread mt([]()
		{
			while (true)
			{
				if (std::cin.get() == 0x0A)
				{
					KeyEventCapture::keyPressed = true;
				}
			}
		}
	);


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
			std::cout << "Password tested \t: " << line << " :::" << tmp << std::endl;
		}
		if (KeyEventCapture::keyPressed)
		{
			std::chrono::time_point<std::chrono::steady_clock> stop = Time::now();
			fsec fs = (stop - start);
			std::cout << "=======================================" << std::endl;
			std::cout << "Mode \t\t\t: " << this->_digest->Name() << std::endl;
			std::cout << "Time elapsed    \t: " << fs.count() << " s" << std::endl;
			std::cout << "Password count  \t: " << this->counter << std::endl;
			std::cout << "Password tested \t: " << line << " ::: " << tmp << std::endl;
			std::cout << "=======================================" << std::endl;
			KeyEventCapture::keyPressed = false;
		}
		if (tmp == hash)
		{
			if (this->_timer)
			{
				std::chrono::time_point<std::chrono::steady_clock> stop = Time::now();
				fsec fs = (stop - start);
				std::cout << "Time elapsed \t: " << fs.count() << " s" << std::endl;
			}
			if (this->_counter)
			{
				std::cout << "Password number\t: " << this->counter << std::endl;
			}
			input.close();
			return  ToLower(line);
		}
	}
	input.close();
	if (this->_timer)
	{
		std::chrono::time_point<std::chrono::steady_clock> stop = Time::now();
		fsec fs = (stop - start);
		std::cout << "Time elapsed \t: " << fs.count() << " s" << std::endl;
	}
	if (this->_counter)
	{
		std::cout << "Password number\t: " << this->counter << std::endl;
	}
	return  ToLower(hash);

}