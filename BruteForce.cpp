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

std::string BruteForcing(std::string hash, IDigest* mode, char alpa[], bool verbose = false)
{
    /*Alphabet = alpa;
    char[] tmp = [Alphabet[0]];
    writefln("Start : %s", Clock.currTime());

    while (true)
    {
        for (int i = 0; i < Alphabet.length; i++)
        {
            countPassword++;
            if (verbose == true)
            {
                writefln("Password tested : %s :: %s", tmp, toLower(toHexString(mode.digest(tmp))));
            }
            if (toLower(toHexString(mode.digest(tmp))) == hash)
            {
                writefln("Stop : %s", Clock.currTime());
                return format!"%s"(tmp);
            }
            tmp = CheckPassWordLetter(tmp);

        }

    }*/
    return mode->hash(hash);
}

static char* CheckPassWordLetter(char* pass)
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
    return (char*)"test";
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



