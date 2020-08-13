#include "BruteForce.h"

std::string BruteForcing(std::string hash, IDigest mode, char alpa[], bool verbose = false)
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
    return "string";
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


static std::string ToLower(std::string text)
{
    std::transform(text.begin(), text.end(), text.begin(),
        [](unsigned char c) { return std::tolower(c); });
}

