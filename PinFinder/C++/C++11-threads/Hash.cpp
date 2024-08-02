/** Hash.cpp
 * Defines a Hash class that:
 * - Stores a 32-character MD5 hash string and (once decoded) its corresponding pin
 * - finds a corresponding pin to a given hash using toPin()
 * 
 * HINT: a class method can be called by a C++11 thread using "&Hash::functionName"
 *
 * Adapted for CSinParallel.org by Joel Adams, Calvin University.
 * Program modified to use C++ by Steven McKelvey, Calvin University.
 */

#include "Hash.hpp"

/** A hash class that stores information about a given hash and its corresponding pin
 * @pre: usersHash contains the MD5 hash of an PIN_DIGITS-digit pin
 */
Hash::Hash(const string &usersHash) : hash(usersHash) {}

/** testable brute force method to find an PIN_DIGITS-digit pin, given its hash (stored in object; Hash.hash)
 * @pre: hash has been initialized
 *       && MPI_Init() has been called.
 * @post: Hash.pin contains the PIN_DIGITS-digit pin corresponding to userHash.
 * @return: true, if a pin corresponding to userHash is found.
 */
bool Hash::toPin()
{
    long currentNum = 0;                 // current num we're trying
    string currentStr(PIN_DIGITS, '\0'); // string-equiv of currentNum
    string currentHash(34, '\0');        // buf for currentStr's hash
    bool foundPin = false;               // flag for controlling loop

    while (currentNum < pow(10, PIN_DIGITS) && !foundPin)
    {                                           // while untried nums remain
        currentStr = convertToPin(currentNum);  //  convert num to PIN_DIGITS-digit pin
        currentHash = hashUsingMD5(currentStr); //  get hash of that pin
        foundPin = equal(currentHash);          // hash == usersHash?
        ++currentNum;                           //  update num for next pass
    }

    if (foundPin)
        pin = currentStr; // store the hash's corresponding pin if it was found

    return foundPin; // return whether we were successful or not
}

/** convert a number into its PIN_DIGITS-digit char* pin.
 * @param num: the number we want to convert.
 * @return: an PIN_DIGITS-digit pin corresponding to num,
 *        (in char format).
 */
string Hash::convertToPin(long num)
{
    string numStr(PIN_DIGITS, '\0');
    const string VALID_CHARS = "0123456789"; // valid pin characters
    int index;                               // index within VALID_CHARS

    // determine the "base" for the pin string
    int base = VALID_CHARS.length();

    // perform the conversion
    for (int i = PIN_DIGITS - 1; i >= 0; --i)
    {                                   // for digits 0..PIN_DIGITS-1:
        index = num % base;             // - get the next digit
        numStr[i] = VALID_CHARS[index]; // - put its char-equiv in buffer
        num = num / base;               // - prep for the next iteration
    }
    return numStr;
}

/** compute the hash of the current number-string.
 * @param currString: an PIN_DIGITS-digit char* of the num we are currently trying.
 * @pre: strlen(currString) == PIN_DIGITS.
 * @return: the hash of currString.
 */
string Hash::hashUsingMD5(const string &currString)
{
    string currHash(32, '\0');               // stores return value
    unsigned char digest[MD5_DIGEST_LENGTH]; // hash storage (MD5)

    // Compute the hash of the current pin
    MD5((unsigned char *)currString.c_str(), currString.length(), digest);

    // Convert the hash to a base-16 string
    for (int i = 0; i < 16; ++i)
    {
        sprintf(&currHash[i * 2], "%02x", (unsigned char)digest[i]);
    }
    return currHash;
}

/** compare the stored hash to another hash.
 * @param currHash: a char* hash of the current number.
 * @return: true if the two are equal, false otherwise.
 */
bool Hash::equal(const string &currHash)
{
    return currHash == hash;
}
