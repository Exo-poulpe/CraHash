// CraHash.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sstream>

#include "MD5.h"
#include "SHA1.h"
#include "IDigest.h"
#include "BruteForce.h"
#include "WordList.h"

#include "include/args.hxx"
#include "include/CryptoPP/base64.h"
#include "include/CryptoPP/md5.h"
#include "include/CryptoPP/hex.h"
#include "include/CryptoPP/files.h"

int main(int argc, char** argvs)
{
	std::string hMode = "The value of mode select : \n\t1 : MD5\n\t2 : SHA1";
	std::string hAlphabet = "Alphabet value\n\t1 : [a-z]\n\t2 : [a-zA-Z]\n\t3 : [a-zA-Z0-9]\n\t4 : [a-zA-Z0-9\\s]";
	args::ArgumentParser parser("This program test hash and generate somes hash", "Author Exo-poulpe\nExample : ./CraHash --hash -t \"TEST\" -m 1");
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
		default:
			std::cout << "Error unknow mode" << std::endl;
			exit(1);
			break;
		}

		std::cout << digest->info(text) << digest->hash(text) << std::endl;

	}
	else if (args::get(fBrute) && args::get(fCrack) && args::get(fText) != "")
	{
		BruteForce Bf = BruteForce();
		std::string hash = args::get(fText);
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

		std::string result = Bf.BruteForcing(hash, digest, alp, args::get(fVerbose), args::get(fCount), args::get(fTimer));
		if (result == hash) { std::cout << "Hash not found" << std::endl; }
		else
		{
			std::cout << "Hash found : " << "\"" << result << "\"" << std::endl;
		}
	}
	else if (args::get(fWordList) != "" && args::get(fCrack) && args::get(fText) != "")
	{
		std::string hash = args::get(fText);
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
		default:
			exit(1);
			break;
		}
		WordList Word = WordList(args::get(fWordList), digest, args::get(fVerbose), args::get(fCount), args::get(fTimer));
		std::string result = Word.Crack(args::get(fText));
		if (result == hash) { std::cout << "Hash not found" << std::endl; }
		else
		{
			std::cout << "Hash found : " << "\"" << result << "\"" << std::endl;
		}
	}
	else if (args::get(fBench) && args::get(fMode) != 0)
	{
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
		default:
			exit(1);
			break;
		}
		Bf.Benchmark(digest);
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
