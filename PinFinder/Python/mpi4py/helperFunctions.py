''' helperFunctions.py
defines functions used by pinFinder.cpp

Adapted for CSinParallel.org by Steven McKelvey, Calvin University. 
Adapted from the pinFinder.c solution created by Joel Adams, Calvin University.
'''

import hashlib


def findPinFromHash(usersHash):
    '''
    Given a hash, searches through all possible PIN_DIGITS-digit 
    md5 hashes to look for a matching hash.

    Params: usersHash, a 32 character md5 hash
    Returns: the pin that was used to compute the matching hash 
    '''
    # have a loop that goes through all the numbers
    PIN_DIGITS = 8
    i = 0
    while i < pow(10, PIN_DIGITS):
        num = str(i)
        pinStr = '0' * (PIN_DIGITS - len(num)) + num # convert to PIN_DIGITS digit pin, padding the left side with 0s
        currentHash = hashlib.md5(pinStr.encode()).hexdigest() # get hash for that pin
        if usersHash == currentHash: return pinStr # compare the hash with the input hash (usersHash)
        i += 1
