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

#include "include/args.hxx"
#include "include/CryptoPP/base64.h"
#include "include/CryptoPP/md5.h"
#include "include/CryptoPP/hex.h"
#include "include/CryptoPP/files.h"

int main(int argc, char** argvs)
{
	std::string hMode = "The value of mode select : \n\t1 : MD5";
	std::string hAlphabet = "Alphabet value\n\t1 : [a-z]\n\t2 : [a-zA-Z]\n\t3 : [a-zA-Z0-9]";
	args::ArgumentParser parser("This program test hash and generate somes hash", "Author Exo-poulpe\nExample : ./CraHash --hash -t \"TEST\" -m 1");
	args::Group group(parser, "This group is all exclusive:", args::Group::Validators::DontCare);
	args::Flag fVerbose(group, "verbose", "Verbosity of program", { 'v',"verbose" });
	args::Flag fCount(group, "count", "Print count", { "count" });
	args::Flag fBrute(group, "brute", "Use brute force", { "brute" });
	args::Flag fHash(group, "hash", "Use hash", { "hash" });
	args::ValueFlag<std::string> fText(group, "text", "The text to use", { 't', "text" });
	args::ValueFlag<std::string> fWordList(group, "wordlist", "The wordlist to use", { 'w',"wordlist" });
	args::ValueFlag<int> fMode(group, "Mode value", hMode, { 'm' });
	args::ValueFlag<int> fAlphabet(group, "Alphabet value", hAlphabet, { 'a' });
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
