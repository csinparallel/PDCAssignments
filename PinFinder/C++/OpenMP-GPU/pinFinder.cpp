/** pinFinder.c
 * ... takes a hash and attempts to find a matching PIN_DIGITS-digit pin
 *
 * Adapted for CSinParallel.org by Joel Adams, Calvin University.
 * Adapted from an EduHPC-2019 Peachy Parallel Assignment
 *  by Daniel Ellsworth, Colorado College,
 *  and Allen Maloney, University of Oregon.
 *
 *  Usage: ./pinFinder <pin-hash>
 *
 *  See: tests.c for some example pin-hash strings
 *        or use ./genHash to generate your own.
 *
 *  Note: Using this sequential version on a good workstation,
 *         finding 00000000 from its hash takes ~0.000015 secs,
 *         finding 12345678 from its hash takes ~14.5 secs,
 *         finding 99999999 from its hash takes ~115.6 secs.
 */

#include "helperFunctions.hpp" // findPinFromHash

int main(int argc, char **argv)
{
    // process command line arguments
    if (argc != 2)
    {
        printf("Usage: %s <pin-hash>\n", argv[0]);
        return 1;
    }

    double startTime = omp_get_wtime(); // start timing

    char pin[PIN_BUF_SIZE] = {0};                            // create buffer for pin
    bool success = findPinFromHash(argv[1], pin); // find pin, put it in buffer

    double totalTime = omp_get_wtime() - startTime; // stop timing

    if (success)
    {
        printf("Found pin '%s' in %lf secs\n", pin, totalTime);
    }
    else
    {                   // otherwise:
        fprintf(stderr, //   print error msg and quit
                "\nUnable to find pin for hash '%s'\n\n",
                argv[1]);
    }

    return 0;
}
