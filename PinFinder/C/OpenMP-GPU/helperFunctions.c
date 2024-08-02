/** helperFunctions.c
 * ... defines functions used by pinFinder.c
 *
 * Adapted for CSinParallel.org by Joel Adams, Calvin University.
 */

#include "helperFunctions.h"
#include "md5.c"

/** testable brute force method to find an PIN_DIGITS-digit pin, given its hash
 * @param usersHash, the hash of the pin being recovered.
 * @param pinStr, a buffer to which we can write that pin.
 * @pre: usersHash contains the MD5 hash of an PIN_DIGITS-digit pin
 *          && strlen(pinStr) == PIN_BUF_SIZE.
 * @post: pinStr contains the PIN_DIGITS-digit pin corresponding to usersHash.
 */
bool findPinFromHash(const char *usersHash, char *pinStr)
{
    const int REPS = pow(10, PIN_DIGITS);

    long currentNum = 0;        // num we'll try, start at 0
    char currentStr[PIN_BUF_SIZE] = {0};   // string-equiv of currentNum
    char currentHash[34] = {0}; // buffer for currentStr's hash
    bool foundPin = false;      // flag for controlling loop

    // brute-force: try each number
    while (currentNum < REPS && !foundPin)
    {                                             // while numbers remain:
        convertToPin(currentNum, currentStr);     //  convert num to PIN_DIGITS-digit pin
        hashUsingMD5(currentStr, currentHash);    //  get hash of that pin
        foundPin = equal(currentHash, usersHash); //  compare hash to usersHash,
        ++currentNum;                             //  prep for next iteration
    }

    if (foundPin)
    {                                   // if we found a match:
        memcpy(pinStr, currentStr, PIN_BUF_SIZE); //   copy it into the pinStr buffer
        foundPin = true;
    }

    return foundPin;
}

/** convert a number into its PIN_DIGITS-digit char* pin.
 * @param num, the number we want to convert.
 * @param numStr, a null-terminated char* buffer
 *          for the PIN_DIGITS-digit pin corresponding to num.
 * @pre: strln(numStr) == PIN_BUF_SIZE.
 * @post: numStr contains the PIN_DIGITS-digit pin corresponding to num,
 *        (in char format).
 */
void convertToPin(int num, char *numStr)
{
    const char *VALID_CHARS = "0123456789"; // valid pin characters
    int index;                              // index within VALID_CHARS

    // determine the "base" for the pin string
    int base = 10;

    // perform the conversion
    for (int i = PIN_DIGITS - 1; i >= 0; --i)
    {                                   // for digits 0..PIN_DIGITS-1:
        index = num % base;             // - get the next digit
        numStr[i] = VALID_CHARS[index]; // - put its char-equiv in buffer
        num = num / base;               // - prep for the next iteration
    }
}

/** compare two hashes.
 * Manual implementation received from ChatGPT on 5/9/24.
 * This implementation of "equal()" is compatible with accelerators.
 * @param currHash, a char* hash of the current number.
 * @param usersHash, a char* hash of the forgotten pin.
 * @return: true if the two are equal, false otherwise.
 */
bool equal(const char *currHash, const char *usersHash)
{
    while (*currHash != '\0' && *usersHash != '\0')
    {
        if (*currHash != *usersHash)
        {
            return false; // Characters are different, strings are not equal
        }
        ++currHash;  // Move to the next character in str1
        ++usersHash; // Move to the next character in str2
    }
    // If both strings are at their end ('\0'), they are equal
    return (*currHash == '\0' && *usersHash == '\0');
}