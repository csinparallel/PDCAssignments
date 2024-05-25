'''tests.py
Tests the PinCracker function for 
finding a pin from a hash string.

Steven McKelvey, Calvin University, May 2024.
Based on C tests made by Joel Adams, Calvin University.

Usage: python tests.py

Note: The final test (#4) will take some time
        since it is searching through all 
        permutations of 8-digit pins
'''

import subprocess
from helperFunctions import findPinFromHash

def main():
    print("\nTesting hashes... ")

    hash = subprocess.run("./genHash.sh 00000000 | cut -c 1-32", shell = True, capture_output = True, text = True).stdout.strip() # strip gets rid of newline
    assert "00000000" == findPinFromHash(hash)
    print (" 0 ", end=" ")

    hash = subprocess.run("./genHash.sh 00000001 | cut -c 1-32", shell = True, capture_output = True, text = True).stdout.strip()
    assert("00000001" == findPinFromHash(hash))
    print (" 1 ", end=" ")

    hash = subprocess.run("./genHash.sh 00050000 | cut -c 1-32", shell = True, capture_output = True, text = True).stdout.strip()
    assert("00050000" == findPinFromHash(hash))
    print (" 2 ", end=" ")

    hash = subprocess.run("./genHash.sh 10000000 | cut -c 1-32", shell = True, capture_output = True, text = True).stdout.strip()
    assert("10000000" == findPinFromHash(hash))
    print (" 3 ", end=" ")

    hash = subprocess.run("./genHash.sh abcdefgh | cut -c 1-32", shell = True, capture_output = True, text = True).stdout.strip()
    assert(None == findPinFromHash(hash)) # nothing is returned if nothing is found
    print (" 4 ", end=" ")

    print("\nAll tests passed!\n\n")

main()