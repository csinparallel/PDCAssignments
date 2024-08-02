''' pinFinder.py
takes a hash and attempts to find a matching PIN_DIGITS-digit pin

Uses the mpi4py package for MPI support.

Adapted for CSinParallel.org by Steven McKelvey, Calvin University. 
Adapted from the pinFinder.c solution created by Joel Adams, Calvin University.

Usage: mpiexec -n <num_processes> python3 pinFinder.py <pin-hash>
'''
import sys # command line arguments
import time # timing functions
from mpi4py import MPI
from helperFunctions import findPinFromHash

def main():
    # check command line arguments
    if (len(sys.argv) != 2):
        print(f"Usage: python3 {sys.argv[0]} <pin-hash>\n")
        exit(1)

    # timing start
    startTime = time.time()

    pin = findPinFromHash(sys.argv[1])

    # timing end
    totalTime = time.time() - startTime
    
    if (pin != None): 
        print(f"Found pin {pin} in {totalTime} secs\n")
    else:
        raise Exception(f"Unable to find pin for hash '{sys.argv[1]}'")

main()