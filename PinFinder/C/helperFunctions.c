/* helperFunctions.c 
 * ... defines functions used by pinFinder.c
 *
 * Adapted for CSinParallel.org by Joel Adams, Calvin University.
 */

#include "helperFunctions.h"

/** testable brute force method to find an 8-digit pin, given its hash
 * @param usersHash, the hash of the pin being recovered.
 * @param pinStr, a buffer to which we can write that pin.
 * PRE: usersHash contains the MD5 hash of an 8-digit pin
 *          && strlen(pinStr) == 9.
 * POST: pinStr contains the 8-digit pin corresponding to usersHash.
 */
bool findPinFromHash(const char* usersHash, char* pinStr) {
    const int REPS = 100000000;

    long currentNum = 0;                       // num we'll try, start at 0
    char currentStr[9] = {0};                  // string-equiv of currentNum
    char currentHash[34] = {0};                // buffer for currentStr's hash
    bool foundPin = false;                      // flag for controlling loop
                                               // brute-force: try each number
    while (currentNum < REPS && !foundPin) {     // while numbers remain:
        convertToPin(currentNum, currentStr);        //  convert num to 8-digit pin
        hashUsingMD5(currentStr, currentHash);       //  get hash of that pin
        foundPin = equal(currentHash, usersHash);//  compare hash to usersHash,
        ++currentNum;                                //  prep for next iteration
    }

    if ( foundPin ) {                         // if we found a match:
        strncpy(pinStr, currentStr, 9);        //   copy it into the pinStr buffer
        foundPin = true;
    } 

    return foundPin;
}


/** convert a number into its 8-digit char* pin.
 * @param num, the number we want to convert.
 * @param numStr, a null-terminated char* buffer 
 *          for the 8-digit pin corresponding to num.
 * PRE: strln(numStr) == 9.
 * POST: numStr contains the 8-digit pin corresponding to num,
 *        (in char format).
 */
void convertToPin(long num, char* numStr) {
    const char* VALID_CHARS = "0123456789"; // valid pin characters
    int index;                              // index within VALID_CHARS
    
    // determine the "base" for the pin string
    int base = strlen(VALID_CHARS);
    
    // perform the conversion
    for(int i = 7; i >= 0; --i) {           // for digits 0..7:
        index = num % base;                 // - get the next digit
        numStr[i] = VALID_CHARS[index];     // - put its char-equiv in buffer
        num = num / base;                   // - prep for the next iteration
    }
}


/** compute the hash of the current number-string.
 * @param currString, an 8-digit char* of the num we are currently trying.
 * @param currHash, a buffer for the hash of that pin.
 * PRE: strlen(currString) == 8 && strlen(currHash) == 34.
 * POST: currentHash contains hash(currString).
 */
void hashUsingMD5(const char* currString, char* currHash) {
    unsigned char digest[MD5_DIGEST_LENGTH]; // hash storage
    
    // Compute the hash of the current pin
    MD5((unsigned char*)currString, strlen(currString), digest);
    
    // Convert the hash to a base-16 string
    for(int i = 0; i < 16; ++i) {
        sprintf(&currHash[i*2], "%02x", (unsigned char)digest[i]);
    }
}


/** compare two hashes.
 * @param currHash, a char* hash of the current number.
 * @param usersHash, a char* hash of the forgotten pin.
 * RETURN: true if the two are equal, false otherwise.
 */
bool equal(const char* currHash, const char* usersHash) {
    return strncmp(currHash, usersHash, strlen(usersHash)) == 0;
}

