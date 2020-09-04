# *CraHash* #

**CraHash** is a program for test hash in C++.

*Version : 0.0.1.4*

### Installation ###

*This program is only tested for Windows x64 OS*


Library used : 
 - [Crypto++](https://cryptopp.com/) Version 8.2 - APR/28/2019
 - [Boost](https://www.boost.org/) Version 1.74.0 August 14th, 2020 05:02 GMT

### Usage/Help ###

```
  .\CraHash.exe {OPTIONS}

    This program test hash and generate somes hash

  OPTIONS:

      This group is all exclusive:
        -t[text], --text=[text]           The hash to use or text to hash
        --hash                            Use hash mode for hash text
        --crack                           Try to crack hash with mode (-b , -w)
        -b                                Use brute force (Bruteforce mode)
        -w[wordlist]                      The wordlist to use (Wordlist mode)
        -m[Mode value]                    The value of mode select :
                                           1 : MD5
                                           2 : SHA1
                                           3 : NTLM
        -a[Alphabet value]                Alphabet value
                                           1 : [a-z]
                                           2 : [a-zA-Z]
                                           3 : [a-zA-Z0-9]
                                           4 : [a-zA-Z0-9\s]
        --benchmark                       Test benchmark mode (With mode)
        --count                           Print count
        --simple                          Resume options when start attack
        --timer                           Print time elasped
        -v, --verbose                     Verbosity of program
      -h, --help                        Display this help menu

    Author : Exo-poulpe
    Version : 0.0.1.4
    Example :
    ./CraHash --hash -t "TEST" -m 1 --timer --count
    ./CraHash --crack -b -m 1 -t "f4e0d0452b352a5bf0a1a5f2a65cb88b"
```

### Exemple ###

For exemple :

```
./CraHash --crack -w rockyou.txt -m 1 -t \"1a79a4d60de6718e8e5b326e338ae533\" --timer --count --simple
```

With this command the hash "1a79a4d60de6718e8e5b326e338ae533::example" and use the wordlis lst.txt and with methods MD5

Result :

```
Mode            : MD5
Wordlist used   : D:\Dico\BigFile.txt
Hash to find    : 7ecc19e1a0be36ba2c6f05d06b5d3058
====================================
Time elapsed    : 6.76694 s
Password number : 90444
Hash found      : "weak"
```

### Benchmark ###

```
Mode            : MD5
Password tested : 1000000
====================================
Time elapsed    : 65.7463 s
Speed           : ~1.6899 [KH/s]

```

For benchmark CraHash test 1'000'000 MD5 hash (default), the result is not very accurate

### Features ###

You can press ENTER key when you crack hash for info

```
=======================================
Mode                    : MD5
Time elapsed            : 12.3861 s
Password count          : 150859
Password tested         : gdoh ::: b7dfb4a85939fffe2c7735c20f2f1489
=======================================
```