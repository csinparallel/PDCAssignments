/* tests.cpp
 * ... tests the pinFinder function for 
 * finding a pin from a hash string.
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

#include "Hash.hpp"
#include <assert.h>
#include <fstream> // file io

int main(int argc, char** argv) {
    // store the hashed pins for later comparison
    int HASHES = 6; // 1st dimension of hash
    string hash[6];

    // print the hashed test pins to a file
    system("./genHash.sh 00000000 | cut -c 1-32 > hashes.txt\n"
        "./genHash.sh 00000001 | cut -c 1-32 >> hashes.txt\n"
        "./genHash.sh 00050000 | cut -c 1-32 >> hashes.txt\n"
        "./genHash.sh 10000000 | cut -c 1-32 >> hashes.txt\n"
        "./genHash.sh 99999999 | cut -c 1-32 >> hashes.txt\n"
        "./genHash.sh abcdefgh | cut -c 1-32 >> hashes.txt");

    ifstream fin ("hashes.txt");
    if (fin.is_open()) {
        // read hashes from file and into char arrays
        for (int i = 0; i < HASHES; i++) {
            getline(fin, hash[i]);  // store each hash (from hashes.txt) in an array of strings.
        }

        fin.close();
        remove("hashes.txt");
    } else {
        cout << "Unable to create a file of hashes for testing" << endl;
        return 1;
    }

    printf("\nTesting hashes... "); fflush(stdout);

    Hash hash0(hash[0]);
    bool flag0 = hash0.toPin();
    assert( flag0 );
    assert( "00000000" == hash0.getPin() );
    printf(" 0 "); fflush(stdout);

    Hash hash1(hash[1]);
    bool flag1 = hash1.toPin();
    assert( flag1 );
    assert( "00000001" == hash1.getPin() );
    printf(" 1 "); fflush(stdout);

    Hash hash2(hash[2]);
    bool flag2 = hash2.toPin();
    assert( flag2 );
    assert( "00050000" == hash2.getPin() );
    printf(" 2 "); fflush(stdout);

    Hash hash3(hash[3]);
    bool flag3 = hash3.toPin();
    assert( flag3 );
    assert( "10000000" == hash3.getPin() );
    printf(" 3 "); fflush(stdout);

    Hash hash4(hash[4]);
    bool flag4 = hash4.toPin();
    assert( flag4 );
    assert( "99999999" == hash4.getPin() );
    printf(" 4 "); fflush(stdout);

    Hash hash5(hash[5]);
    bool flag5 = hash5.toPin();
    assert( !flag5 );
    printf(" 5 "); fflush(stdout);

        printf("\nAll tests passed!\n\n");

    return 0;
}
