/* Hash.h 
 *  ... includes libraries and declares functions used by pinFinder.c
 *
 * For CSinParallel.org by Joel Adams, Calvin University.
 * Solution modified to use C++ by Steven McKelvey, Calvin University.
 */

#include <stdio.h>               // sprintf, printf 
#include <iostream>             //
#include <stdlib.h>              // exit
#include <cstring>              // strlen, strncmp
#include <string>               // string type
#include <stdbool.h>             // bool type
#include <openssl/md5.h>         // md5 hash function
#include <omp.h>                 // omp timing

using namespace std;

#define MASTER 0

#define PIN_BOUNDARY 100000000     // upper bound
#define PIN_DIGITS 8               // 00000000..99999999
#define PIN_BUF_SIZE PIN_DIGITS+1  // +1 byte for null char

// A "Hash" class that... 
class Hash{
    // stores information about a given hash and its corresponding pin
    private:
        const string hash;
        string pin = "";
    public:
        Hash(const string& usersHash);
        // toPin() decodes the given hash and stores the result in Hash.pin, 
        // returning whether it was successful or unsuccessful
        bool toPin(); 
        const string getHash() const {return hash;}
        string getPin() const {return pin;}
    // methods used by toPin()
    private:
        string convertToPin(long num);
        string hashUsingMD5(const string& currString);
        bool equal(const string& currHash);
};

