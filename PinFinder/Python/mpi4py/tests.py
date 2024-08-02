'''tests.py
Tests the PinCracker function for 
finding a pin from a hash string.

These tests were designed for a pin length of 8 digits
Other files use the macro defined in helperFunctions.py, 
so change PIN_DIGITS to 8 before running these tests.

Steven McKelvey, Calvin University, May 2024.
Based on C tests made by Joel Adams, Calvin University.

Usage:  mpiexec -n <num_processes> python3 tests.py

Note: The final test (#4) will take some time
        since it is searching through all 
        permutations of 8-digit pins
'''

''' Example Hashes:
 dd4b21e9ef71e1291183a46b913ae6f2 == genHash(00000000)
 ced165163e51e06e01dc44c35fea3eaf == genHash(00000001)
 f5e47d6221e924f5d1365eb89aad6098 == genHash(00050000)
 d1ca3aaf52b41acd68ebb3bf69079bd1 == genHash(10000000)
'''

import subprocess
from mpi4py import MPI
from helperFunctions import findPinFromHash

# ensure only the MASTER process is testing/printing
MASTER = 0

def main():
    id = -1
    comm = MPI.COMM_WORLD
    id = comm.Get_rank()

    if id == MASTER: print("\nTesting hashes... ")

    hash0 = subprocess.run("./genHash.sh 00000000 | cut -c 1-32", shell = True, capture_output = True, text = True).stdout.strip() # strip gets rid of newline
    flag0 = "00000000" == findPinFromHash(hash0)
    if id == MASTER:
        assert flag0
        print (" 0 ", end=" ")    

    hash1 = subprocess.run("./genHash.sh 00000001 | cut -c 1-32", shell = True, capture_output = True, text = True).stdout.strip()
    flag1 = "00000001" == findPinFromHash(hash1)
    if id == MASTER:
        assert flag1
        print (" 1 ", end=" ")

    hash2 = subprocess.run("./genHash.sh 00050000 | cut -c 1-32", shell = True, capture_output = True, text = True).stdout.strip()
    flag2 = "00050000" == findPinFromHash(hash2)
    if id == MASTER:
        assert flag2
        print (" 2 ", end=" ")

    hash3 = subprocess.run("./genHash.sh 10000000 | cut -c 1-32", shell = True, capture_output = True, text = True).stdout.strip()
    flag3 = "10000000" == findPinFromHash(hash3)
    if id == MASTER:
        assert flag3
        print (" 3 ", end=" ")

    hash4 = subprocess.run("./genHash.sh abcdefgh | cut -c 1-32", shell = True, capture_output = True, text = True).stdout.strip()
    flag4 = None == findPinFromHash(hash4) # nothing is returned if nothing is found
    if id == MASTER:
        assert flag4
        print (" 4 ", end=" ")

    if id == MASTER: print("\nAll tests passed!\n\n")

main()