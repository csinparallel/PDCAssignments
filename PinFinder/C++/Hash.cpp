/* Hash.cpp 
 * Defines a Hash class that:
 * - Stores a 32-character MD5 hash string and (once decoded) its corresponding pin
 * - finds a corresponding pin to a given hash using toPin()
 *
 * Adapted for CSinParallel.org by Joel Adams, Calvin University.
 * Solution modified to use C++ by Steven McKelvey, Calvin University.
 */

#include "Hash.hpp"

/** A hash class that stores information about a given hash and its corresponding pin
 * PRE: usersHash contains the MD5 hash of an 8-digit pin
*/
Hash::Hash(const string& usersHash) : hash(usersHash) { }


/** testable brute force method to find an 8-digit pin, given its hash (stored in object; Hash.hash)
* PRE: hash has been initialized 
*       && MPI_Init() has been called.
* POST: Hash.pin contains the 8-digit pin corresponding to userHash.
* RETURN: true, if a pin corresponding to userHash is found.
*/
bool Hash::toPin() {
    long currentNum = 0;                          // current num we're trying
    string currentStr(8, '\0');                          // string-equiv of currentNum
    string currentHash(34, '\0');;                    // buf for currentStr's hash
    bool foundPin = false;                      // flag for controlling loop

                                                 
    while (currentNum < PIN_BOUNDARY && !foundPin) {// while untried nums remain
        currentStr = convertToPin(currentNum);      //  convert num to 8-digit pin
        currentHash = hashUsingMD5(currentStr);     //  get hash of that pin
        foundPin = equal(currentHash);              // hash == usersHash?
        ++currentNum;                    //  update num for next pass
    }

    if ( foundPin ) this->pin = currentStr;        // store the hash's corresponding pin if it was found

    return foundPin;                        // return whether we were successful or not
}


/** convert a number into its 8-digit char* pin.
* @param num, the number we want to convert.
* RETURN: an 8-digit pin corresponding to num,
*        (in char format).
*/
string Hash::convertToPin(long num) {
    string numStr(8, '\0');
    const string VALID_CHARS = "0123456789"; // valid pin characters
    int index;                              // index within VALID_CHARS
    
    // determine the "base" for the pin string
    int base = VALID_CHARS.length();
    
    // perform the conversion
    for(int i = 7; i >= 0; --i) {           // for digits 0..7:
        index = num % base;                 // - get the next digit
        numStr[i] = VALID_CHARS[index];     // - put its char-equiv in buffer
        num = num / base;                   // - prep for the next iteration
    }
    return numStr;
}


/** compute the hash of the current number-string.
* @param currString, an 8-digit char* of the num we are currently trying.
* PRE: strlen(currString) == 8.
* RETURN: the hash of currString.
*/
string Hash::hashUsingMD5(const string& currString) {
    string currHash(32, '\0'); // stores return value
    unsigned char digest[MD5_DIGEST_LENGTH]; // hash storage (MD5)
    
    // Compute the hash of the current pin
    MD5((unsigned char*)currString.c_str(), currString.length(), digest);
    
    // Convert the hash to a base-16 string
    for(int i = 0; i < 16; ++i) {
        sprintf(&currHash[i*2], "%02x", (unsigned char)digest[i]);
    }
    return currHash;
}


/** compare the stored hash to another hash.
* @param currHash, a char* hash of the current number.
* RETURN: true if the two are equal, false otherwise.
*/
bool Hash::equal(const string& currHash) {
    return currHash == this->hash;
}
