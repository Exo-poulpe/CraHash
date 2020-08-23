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

std::string BruteForce::BruteForcing(std::string hash, IDigest* mode, std::string alpa, int min, int max, bool verbose, bool counter, bool timer)
{
	for (int i = 0; i < alpa.size(); i++)
	{
		Alphabet.push_back(alpa.at(i));
	}

	std::string tmp;
	tmp.append(min, Alphabet[0]);
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
				std::cout << "Password tested : " << tmp << " ::: " << mode->hash(tmp) << std::endl;
			}
			if (mode->hash(tmp) == hash)
			{
				if (timer)
				{
					std::chrono::time_point<std::chrono::steady_clock> stop = Time::now();
					fsec fs = (stop - start);
					std::cout << "Time elapsed : " << fs.count() << " s" << std::endl;
				}
				if (counter)
				{
					std::cout << "Password tested : " << countPassword << std::endl;
				}
				return tmp;
			}
			tmp = CheckPassWordLetter(tmp);
			if (hash == "" && countPassword == 1000000)
			{
				std::chrono::time_point<std::chrono::steady_clock> stop = Time::now();
				fsec fs = (stop - start);
				std::cout << "Mode : " << mode->Name() << std::endl;
				std::cout << "Time elapsed : " << fs.count() << " s" << std::endl;
				std::cout << "Password tested : " << countPassword << std::endl;
				double perSec = (double)fs.count() / countPassword;
				double numberInt = (double)1 / perSec;
				int countNumber = 0;
				std::string unitNumber = "[KH/s]";

				while (numberInt > 1000)
				{
					if (countNumber == 0)
					{
						numberInt /= 1000;
						countNumber += 1;
					}
					else if (countNumber == 1)
					{
						numberInt /= 1000;
						countNumber += 1;
						unitNumber = "[MH/s]";
					}
					else if (countNumber == 2)
					{
						numberInt /= 1000;
						countNumber += 1;
						unitNumber = "[GH/s]";
					}
				}

				std::cout << "Speed : " << std::fixed << std::setprecision(3) << numberInt << " " << unitNumber << std::endl;

				return hash;
			}

		}

	}
	return hash;
}

void BruteForce::Benchmark(IDigest* digest)
{
	BruteForcing("", digest, this->ALPHABET, 1, 5, false, true, true);
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



