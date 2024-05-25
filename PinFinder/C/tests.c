/* tests.c
 * ... tests the PinCracker function for 
 * finding a pin from a hash string.
 *
 * Joel Adams, Calvin University, Nov 2019.
 * Modified to generate hashes from genHash.sh 
 *  by Steven McKelvey, Calvin University, May 2024.
 *
 * Usage: ./tests
 *
 * Note: test #3 and #4 take a few seconds, so be patient...
 */

#include "helperFunctions.h"
#include <assert.h>
#include <stdio.h>

int main() {
    printf("\nTesting hashes... "); fflush(stdout);

    int HASHES = 5; // 1st dimension of hash
    char hash[5][34] = {0};

    // print the hashed test pins to a file
    system("./genHash.sh 00000000 | cut -c 1-32 > hashes.txt\n"
        "./genHash.sh 00000001 | cut -c 1-32 >> hashes.txt\n"
        "./genHash.sh 00050000 | cut -c 1-32 >> hashes.txt\n"
        "./genHash.sh 10000000 | cut -c 1-32 >> hashes.txt\n"
        "./genHash.sh abcdefgh | cut -c 1-32 >> hashes.txt");

    FILE *fin;
    fin = fopen("hashes.txt", "r");

    // read hashes from file and into char arrays
    for (int i = 0; i < HASHES; i++) {
        fgets(hash[i], 32, fin); // get a hash
        fseek(fin, 2, SEEK_CUR); //skip to the end of the line
    }

    fclose(fin);
    remove("hashes.txt");

    bool status;

    char test0[9] = {0};
    status = findPinFromHash(hash[0], test0);
    assert( !strncmp("00000000", test0, 8) );
    assert( status );
    printf(" 0 "); fflush(stdout);

    char test1[9] = {0};
    status = findPinFromHash(hash[1], test1);
    assert( !strncmp("00000001", test1, 8) );
    assert( status );
    printf(" 1 "); fflush(stdout);

    char test2[9] = {0};
    status = findPinFromHash(hash[2], test2);
    assert( !strncmp("00050000", test2, 8) );
    assert( status );
    printf(" 2 "); fflush(stdout);

    char test3[9] = {0};
    status = findPinFromHash(hash[3], test3);
    assert( !strncmp("10000000", test3, 8) );
    assert( status );
    printf(" 3 "); fflush(stdout);
    
    // invalid input ("abcdefgh")
    char test4[9] = {0};
    status = findPinFromHash(hash[4], test4);
    assert( strncmp("abcdefgh", test4, 8) );
    assert( !status );
    printf(" 4 "); fflush(stdout);

    printf("\nAll tests passed!\n\n");
    

    return 0;
}
