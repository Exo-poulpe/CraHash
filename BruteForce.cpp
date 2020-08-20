#include "BruteForce.h"


std::string BruteForce::ToLower(std::string text)
{
	std::string result;
	result.resize(text.size());
	for (int i = 0; i < text.size(); i++)
	{
		result.at(i) = std::tolower(text.at(i));
	}
	return result;
}

BruteForce::BruteForce()
{

}

std::string BruteForce::BruteForcing(std::string hash, IDigest* mode, std::string alpa, bool verbose)
{
	for (int i = 0; i < alpa.size(); i++)
	{
		Alphabet.push_back(alpa.at(i));
	}

	std::string tmp;
	tmp.append(1, Alphabet[0]);
	typedef std::chrono::high_resolution_clock Time;
	typedef std::chrono::duration<float> fsec;
	std::chrono::time_point<std::chrono::steady_clock> start = Time::now();


	while (true)
	{
		for (int i = 0; i < Alphabet.size(); i++)
		{
			countPassword++;
			if (countPassword == 475252)
			{
				countPassword = countPassword;
			}
			if (verbose == true)
			{
				std::cout << "Password tested : " << tmp << " ::: " << ToLowerToHex(mode->hash(tmp)) << std::endl;
			}
			if (mode->hash(tmp) == hash)
			{
				//std::chrono::system_clock::time_point stop = std::chrono::system_clock::now();
				std::chrono::time_point<std::chrono::steady_clock> stop = Time::now();
				fsec fs = (stop - start);
				std::cout << "Time elapsed : " << fs.count() << " s"  << std::endl;
				return tmp;
			}
			tmp = CheckPassWordLetter(tmp);

		}

	}
	return hash;
}

std::string BruteForce::ToLowerToHex(std::string text)
{
	std::string res;
	CryptoPP::StringSource ss(text, true,
		new CryptoPP::HexEncoder(new CryptoPP::StringSink(res)
		));

	return res;
}


std::string BruteForce::CheckPassWordLetter(std::string pass)
{

	int Turn = 1;
	for (int i = 0; i < Turn; i++)
	{
		if (pass[i] == Alphabet[Alphabet.size() - 1])
		{
			if (pass.size() > i + 1)
			{
				pass[i] = Alphabet[0];
				Turn++;
			}
			else
			{
				pass.append(1, Alphabet[0]);
				pass[i] = Alphabet[0];
			}

		}
		else
		{
			pass[i] = NewCharFromChar(pass[i]);
		}
	}
	return pass;
}

char BruteForce::NewCharFromChar(char letter)
{
	for (int i = 0; i < Alphabet.size(); i++)
	{
		if (letter == Alphabet[i])
		{
			if ((i + 1) > Alphabet.size() - 1)
				return Alphabet[0];
			else
				return Alphabet[i + 1];
		}
	}
	return Alphabet[0];
}



