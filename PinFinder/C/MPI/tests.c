/** tests.c
 * ... tests the pinFinder function for
 * finding a pin from a hash string.
 *
 * These tests were designed for a pin length of 8 digits
 * Other files use the macro defined in helperFunctions.h, 
 * so change PIN_DIGITS to 8 before running these tests.
 *
 * Joel Adams, Calvin University, Nov 2019.
 * Modified to generate hashes from genHash.sh
 *  by Steven McKelvey, Calvin University, May 2024.
 *
 * Usage: ./tests
 *
 * Note: test #3 takes a few seconds, and
 *       tests 4 & 5 take a few minutes each, so be patient...
 */

/** Example Hashes:
 * dd4b21e9ef71e1291183a46b913ae6f2 == genHash(00000000)
 * ced165163e51e06e01dc44c35fea3eaf == genHash(00000001)
 * f5e47d6221e924f5d1365eb89aad6098 == genHash(00050000)
 * d1ca3aaf52b41acd68ebb3bf69079bd1 == genHash(10000000)
 */

#include "helperFunctions.h"
#include <assert.h>

#define MASTER 0

int main(int argc, char **argv)
{
    // store the hashed pins for later comparison
    int HASHES = 6; // 1st dimension of hash
    char hash[6][34] = {0};

    // print the hashed test pins to a file
    system("./genHash.sh 00000000 | cut -c 1-32 > hashes.txt\n"
           "./genHash.sh 00000001 | cut -c 1-32 >> hashes.txt\n"
           "./genHash.sh 00050000 | cut -c 1-32 >> hashes.txt\n"
           "./genHash.sh 10000000 | cut -c 1-32 >> hashes.txt\n"
           "./genHash.sh 99999999 | cut -c 1-32 >> hashes.txt\n"
           "./genHash.sh abcdefgh | cut -c 1-32 >> hashes.txt");

    FILE *fin;
    fin = fopen("hashes.txt", "r");

    // read hashes from file and into char arrays
    for (int i = 0; i < HASHES; ++i)
    {
        fgets(hash[i], 32, fin); // get a hash
        fseek(fin, 2, SEEK_CUR); // skip to the end of the line
    }

    fclose(fin);
    remove("hashes.txt");

    // MPI Setup
    int id = -1;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);

    if (id == MASTER)
    {
        printf("\nTesting hashes... ");
        fflush(stdout);
    }

    char test0[PIN_BUF_SIZE] = {0};
    bool flag0 = findPinFromHash(hash[0], test0);
    if (id == MASTER)
    {
        assert(flag0);
        assert(!strncmp("00000000", test0, PIN_BUF_SIZE)); // NOTE: strncmp returns 0 if there are no differences.
        printf(" 0 ");
        fflush(stdout);
    }

    char test1[PIN_BUF_SIZE] = {0};
    bool flag1 = findPinFromHash(hash[1], test1);
    if (id == MASTER)
    {
        assert(flag1);
        assert(!strncmp("00000001", test1, PIN_BUF_SIZE));
        printf(" 1 ");
        fflush(stdout);
    }

    char test2[PIN_BUF_SIZE] = {0};
    bool flag2 = findPinFromHash(hash[2], test2);
    if (id == MASTER)
    {
        assert(flag2);
        assert(!strncmp("00050000", test2, PIN_BUF_SIZE));
        printf(" 2 ");
        fflush(stdout);
    }

    char test3[PIN_BUF_SIZE] = {0};
    bool flag3 = findPinFromHash(hash[3], test3);
    if (id == MASTER)
    {
        assert(flag3);
        assert(!strncmp("10000000", test3, PIN_BUF_SIZE));
        printf(" 3 ");
        fflush(stdout);
    }

    char test4[PIN_BUF_SIZE] = {0};
    bool flag4 = findPinFromHash(hash[4], test4);
    if (id == MASTER)
    {
        assert(flag4);
        assert(!strncmp("99999999", test4, PIN_BUF_SIZE));
        printf(" 4 ");
        fflush(stdout);
    }

    char test5[PIN_BUF_SIZE] = {0}; // this test (for a non-existent pin) should 'fail'...
    bool flag5 = findPinFromHash(hash[5], test5);
    if (id == MASTER)
    {
        assert(!flag5);
        printf(" 5 ");
        fflush(stdout);
    }

    if (id == MASTER)
    {
        printf("\nAll tests passed!\n\n");
    }

    MPI_Finalize();
    return 0;
}
