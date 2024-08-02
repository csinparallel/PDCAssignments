/** helperFunctions.h
 *  ... includes libraries and declares functions used by pinFinder.c
 *
 * For CSinParallel.org by Joel Adams, Calvin University.
 */

#include <stdio.h>       // sprintf, printf
#include <stdlib.h>      // exit
#include <string.h>      // strlen, strncmp
#include <stdbool.h>     // bool type
#include <math.h>        // pow()
#include <openssl/md5.h> // md5 hash function
#include <omp.h>         // omp timing

#define PIN_DIGITS 8                // 00000000..99999999
#define PIN_BUF_SIZE PIN_DIGITS + 1 // +1 byte for null char

bool findPinFromHash(const char *usersHash, char *pinStr);
void convertToPin(long currentNum, char *currentStr);
void hashUsingMD5(const char *currentString, char *currentHash);
bool equal(const char *currentHash, const char *userHash);
