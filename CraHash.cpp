// CraHash.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sstream>

#include "MD5.h"
#include "NTLM.h"
#include "SHA1.h"
#include "IDigest.h"
#include "BruteForce.h"
#include "WordList.h"

#include "include/args.hxx"
#include "boost/thread/thread.hpp"
#include "include/CryptoPP/base64.h"
#include "include/CryptoPP/md5.h"
#include "include/CryptoPP/hex.h"
#include "include/CryptoPP/files.h"

std::string ToLower(std::string text)
{
	std::string result;
	result.resize(text.size());
	for (int i = 0; i < text.size(); i++)
	{
		result.at(i) = std::tolower(text.at(i));
	}
	return result;
}


std::string RunDigest(void* tmp, std::string text)
{
	IDigest* digest = (IDigest*)tmp;
	return digest->hash(text);
}

int main(int argc, char** argvs)
{

	std::string hMode = "The value of mode select : \n\t1 : MD5\n\t2 : SHA1\n\t3 : NTLM";
	std::string hAlphabet = "Alphabet value\n\t1 : [a-z]\n\t2 : [a-zA-Z]\n\t3 : [a-zA-Z0-9]\n\t4 : [a-zA-Z0-9\\s]";
	std::string hParser = R"(Author : Exo-poulpe
Version : 0.0.1.3

Example : 
./CraHash --hash -t \"TEST\" -m 1 --timer --count
./CraHash --crack -b -m 1 -t \"f4e0d0452b352a5bf0a1a5f2a65cb88b\")";

	args::ArgumentParser parser("This program test hash and generate somes hash", hParser);
	args::Group group(parser, "This group is all exclusive:", args::Group::Validators::DontCare);
	args::ValueFlag<std::string> fText(group, "text", "The hash to use or text to hash", { 't', "text" });
	args::Flag fHash(group, "hash", "Use hash mode for hash text", { "hash" });
	args::Flag fCrack(group, "crack", "Try to crack hash with mode (-b , -w)", { "crack" });
	args::Flag fBrute(group, "brute", "Use brute force (Bruteforce mode)", { 'b' });
	args::ValueFlag<std::string> fWordList(group, "wordlist", "The wordlist to use (Wordlist mode)", { 'w' });
	args::ValueFlag<int> fMode(group, "Mode value", hMode, { 'm' });
	args::ValueFlag<int> fAlphabet(group, "Alphabet value", hAlphabet, { 'a' });
	args::Flag fBench(group, "benchmark", "Test benchmark mode (With mode)", { "benchmark" });
	args::Flag fCount(group, "count", "Print count", { "count" });
	args::Flag fSimple(group, "simple", "Resume options when start attack", { "simple" });
	args::Flag fTimer(group, "timer", "Print time elasped", { "timer" });
	args::Flag fVerbose(group, "verbose", "Verbosity of program", { 'v',"verbose" });
	args::HelpFlag help(parser, "help", "Display this help menu", { 'h', "help" });

	try
	{
		parser.ParseCLI(argc, argvs);
	}
	catch (args::Help)
	{
		std::cout << parser;
		return 0;
	}
	catch (args::ParseError e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << parser;
		return 1;
	}
	catch (args::ValidationError e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << parser;
		return 1;
	}
	if (argc <= 1)
	{
		std::cout << parser << std::endl;
	}
	if (args::get(fHash) && args::get(fText) != "")
	{
		IDigest* digest;
		int alpha = 3;
		std::string text = args::get(fText);
		if (args::get(fAlphabet))
		{
			alpha = args::get(fAlphabet);
		}
		switch (args::get(fMode))
		{
		case 1:
			digest = &MD5(text);
			break;
		case 2:
			digest = &SHA1(text);
			break;
		case 3:
			digest = &NTLM(text);
			break;
		default:
			std::cout << "Error unknow mode" << std::endl;
			exit(1);
			break;
		}

		std::cout << digest->info(text) << digest->hash(text) << std::endl;

	}
	else if (args::get(fBrute) && args::get(fCrack) && args::get(fText) != "" && args::get(fAlphabet) != NULL)
	{
		BruteForce Bf = BruteForce();
		std::string hash = ToLower(args::get(fText));
		IDigest* digest;
		int mode = args::get(fMode);
		switch (mode)
		{
		case 1:
			if (hash.size() != MD5::LENGTH)
			{
				std::cout << "Size of hash not valid" << std::endl;
				exit(1);
			}
			digest = &MD5(hash);
			break;
		case 2:
			if (hash.size() != SHA1::LENGTH)
			{
				std::cout << "Size of hash not valid" << std::endl;
				exit(1);
			}
			digest = &SHA1(hash);
			break;
		case 3:
			if (hash.size() != NTLM::LENGTH)
			{
				std::cout << "Size of hash not valid" << std::endl;
				exit(1);
			}
			digest = &NTLM(hash);
			break;
		default:
			exit(1);
			break;
		}

		int alpa = args::get(fAlphabet);
		std::string alp;
		switch (alpa)
		{
		case 1:
			alp = Bf.ALPHABET;
			break;
		case 2:
			alp = Bf.ALPHABET_UPPER;
			break;
		case 3:
			alp = Bf.ALPHABET_UPPER_NUMBER;
			break;
		case 4:
			alp = Bf.ALPHABET_UPPER_NUMBER_SPECIAL;
			break;
		default:
			break;
		}
		if (args::get(fSimple))
		{
			std::cout << "Mode \t\t: " << digest->Name() << std::endl;
			std::cout << "Hash to find \t: " << args::get(fText) << std::endl;
			std::cout << "====================================" << std::endl;
		}
		std::string result = Bf.BruteForcing(hash, digest, alp, 1, 0, args::get(fVerbose), args::get(fCount), args::get(fTimer));
		if (result == hash) { std::cout << "Hash not found" << std::endl; }
		else
		{
			std::cout << "Hash found \t: " << "\"" << result << "\"" << std::endl;
		}
	}
	else if (args::get(fWordList) != "" && args::get(fCrack) && args::get(fText) != "")
	{
		std::string hash = ToLower(args::get(fText));
		IDigest* digest;
		int mode = args::get(fMode);
		switch (mode)
		{
		case 1:
			if (hash.size() != MD5::LENGTH)
			{
				std::cout << "Size of hash not valid" << std::endl;
				exit(1);
			}
			digest = &MD5(hash);
			break;
		case 2:
			if (hash.size() != SHA1::LENGTH)
			{
				std::cout << "Size of hash not valid" << std::endl;
				exit(1);
			}
			digest = &SHA1(hash);
			break;
		case 3:
			if (hash.size() != NTLM::LENGTH)
			{
				std::cout << "Size of hash not valid" << std::endl;
				exit(1);
			}
			digest = &NTLM(hash);
			break;
		default:
			exit(1);
			break;
		}

		if (args::get(fSimple))
		{
			std::cout << "Mode \t\t: " << digest->Name() << std::endl;
			std::cout << "Wordlist used \t: " << args::get(fWordList) << std::endl;
			std::cout << "Hash to find \t: " << args::get(fText) << std::endl;
			std::cout << "====================================" << std::endl;
		}
		WordList Word = WordList(args::get(fWordList), digest, args::get(fVerbose), args::get(fCount), args::get(fTimer));
		std::string result = Word.Crack(args::get(fText));
		if (result == hash) { std::cout << "Hash not found" << std::endl; }
		else
		{
			std::cout << "Hash found \t: " << "\"" << result << "\"" << std::endl;
		}
	}
	else if (args::get(fBench) && args::get(fMode) != 0)
	{
		typedef std::chrono::high_resolution_clock Time;
		typedef std::chrono::duration<float> fsec;
		std::chrono::time_point<std::chrono::steady_clock> start = Time::now();
		BruteForce Bf = BruteForce();
		IDigest* digest;
		int mode = args::get(fMode);
		switch (mode)
		{
		case 1:
			digest = &MD5();
			break;
		case 2:
			digest = &SHA1();
			break;
		case 3:
			digest = &NTLM();
			break;
		default:
			exit(1);
			break;
		}
		int count = 1000000;
		std::cout << "Mode \t\t: " << digest->Name() << std::endl;
		std::cout << "Password tested\t: " << count << std::endl;
		std::cout << "====================================" << std::endl;

		int CORES = static_cast<int>(boost::thread::hardware_concurrency());

		std::vector<std::thread*> t;

		for (unsigned int i = 0; i < count; i += 1)
		{

			std::vector<boost::thread*> threads(std::min(CORES, count));
			for (size_t i = 0; i < threads.size(); ++i) { // Start appropriate number of threads
				threads[i] = new boost::thread(RunDigest, (void*)digest, std::to_string(i));
			}
			for (size_t i = 0; i < threads.size(); ++i) { // Wait for all threads to finish
				threads[i]->join();
				delete threads[i];
				--count;
			}

			//boost::thread _th = boost::thread(RunDigest,(void*)digest ,std::to_string(i));
			//digest->hash(std::to_string(i));
		}

		std::chrono::time_point<std::chrono::steady_clock> stop = Time::now();
		fsec fs = (stop - start);
		std::cout << "Time elapsed \t: " << fs.count() << " s" << std::endl;
		double perSec = (double)fs.count() / 1000000;
		double numberInt = (double)count / fs.count();
		if (args::get(fVerbose))
		{
			std::cout << "count : " << count << " time : " << fs.count() << " Res : " << (unsigned long int)numberInt << std::endl;
		}
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

		std::cout << "Speed \t\t: ~" << std::fixed << std::setprecision(4) << numberInt << " " << unitNumber << std::endl;
		//Bf.Benchmark(digest);
	}

}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
