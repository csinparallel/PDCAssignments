''' helperFunctions.py
defines functions used by pinFinder.cpp

Adapted for CSinParallel.org by Steven McKelvey, Calvin University. 
Adapted from the pinFinder.c solution created by Joel Adams, Calvin University.
'''

import hashlib


def findPinFromHash(usersHash):
    '''
    Given a hash, searches through all possible 8-digit 
    md5 hashes to look for a matching hash.

    Params: usersHash, a 32 character md5 hash
    Returns: the pin that was used to compute the matching hash 
    '''
    # have a loop that goes through all the numbers
    PIN_BOUND = 100000000
    PIN_LENGTH = 8
    i = 0
    while i < PIN_BOUND:
        num = str(i)
        pinStr = '0' * (PIN_LENGTH - len(num)) + num # convert to 8 digit pin, padding the left side with 0s
        currentHash = hashlib.md5(pinStr.encode()).hexdigest() # get hash for that pin
        if usersHash == currentHash: return pinStr # compare the hash with the input hash (usersHash)
        i += 1
