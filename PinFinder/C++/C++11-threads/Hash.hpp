/** Hash.hpp
 *  ... includes libraries and declares functions used by pinFinder.c
 *
 * For CSinParallel.org by Joel Adams, Calvin University.
 * Solution modified to use C++ by Steven McKelvey, Calvin University.
 */

#ifndef HASH
#define HASH

#include <stdio.h>       // sprintf, printf
#include <iostream>      // Support for C++ style, stream-based output
#include <stdlib.h>      // exit
#include <cstring>       // strlen, strncmp
#include <string>        // string type
#include <stdbool.h>     // bool type
#include <math.h>        // pow
#include <openssl/md5.h> // md5 hash function
#include <omp.h>         // omp timing
// C++11 concurrency
#include <thread>
#include <vector>

using namespace std;

#define PIN_DIGITS 8                // 00000000..99999999
#define PIN_BUF_SIZE PIN_DIGITS + 1 // +1 byte for null char

// A "Hash" class that stores information about a given hash and its corresponding pin
class Hash
{
public:
    Hash(const string &usersHash);
    // toPin() decodes the given hash and stores the result in Hash.pin,
    // returning whether it was successful or unsuccessful
    bool toPin();
    const string getHash() const { return hash; }
    string getPin() const { return pin; }

private:
    // methods used by toPin():
    string convertToPin(long num);
    string hashUsingMD5(const string &currString);
    bool equal(const string &currHash);
    // class members
    const string hash;
    string pin = "";
};

#endif