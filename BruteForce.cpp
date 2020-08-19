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
	std::vector<char> Alphabet(alpa.size());
	for (int i = 0; i < alpa.size(); i++)
	{
		Alphabet.push_back(alpa.at(i));
	}

	std::string tmp = std::to_string(Alphabet[0]);
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();


	while (true)
	{
		for (int i = 0; i < Alphabet.size(); i++)
		{
			countPassword++;
			if (verbose == true)
			{
				
				std::cout << "Password tested : " << tmp << " ::: " << ToLowerToHex(mode->hash(tmp)) << std::endl;
			}
			if (ToLowerToHex(mode->hash(tmp)) == hash)
			{
				std::chrono::system_clock::time_point stop = std::chrono::system_clock::now();
				return tmp;
			}
			tmp = CheckPassWordLetter(tmp);

		}

	}
		return mode->hash(hash);
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

	/*int Turn = 1;
	for (int i = 0; i < Turn; i++)
	{
		if (pass[i] == Alphabet[Alphabet.length - 1])
		{
			if (pass.length > i + 1)
			{
				pass[i] = Alphabet[0];
				Turn++;
			}
			else
			{
				pass.insertInPlace(0, Alphabet[0]);
				pass[pass.length - 1] = Alphabet[0];
			}

		}
		else
		{
			pass[i] = NewCharFromChar(pass[i]);
		}
	}
	return pass;*/
	return std::string("test");
}

static char NewCharFromChar(char letter)
{
	/*for (int i = 0; i < Alphabet.length; i++)
	{
		if (letter == Alphabet[i])
		{
			if ((i + 1) > Alphabet.length - 1)
				return Alphabet[0];
			else
				return Alphabet[i + 1];
		}
	}

	return Alphabet[0];*/

	return 'a';
}



