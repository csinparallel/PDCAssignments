/** pinFinder.cpp
 * ... takes a hash and attempts to find a matching PIN_DIGITS-digit pin.
 *
 * Adapted for CSinParallel.org by Joel Adams, Calvin University.
 * Solution modified to use C++ by Steven McKelvey, Calvin University.
 * Adapted from an EduHPC-2019 Peachy Parallel Assignment
 *  by Daniel Ellsworth, Colorado College,
 *  and Allen Maloney, University of Oregon.
 *
 *  Usage: ./pinFinder <pin-hash>
 *
 *  See: tests.c for some example pin-hash strings
 *        or use ../genHash to generate your own.
 *
 */

#include "Hash.hpp" // Hash class

int main(int argc, char **argv)
{
    // process command line arguments
    if (argc < 2)
    {
        cout << "Usage: " << argv[0] << " <pin-hash>" << endl;
        return 1;
    }

    double startTime = omp_get_wtime(); // start timing

    Hash hash(argv[1]);
    bool success = hash.toPin();

    double totalTime = omp_get_wtime() - startTime; // stop timing

    if (success)
    {
        cout << "\nFound pin '" << hash.getPin() << "' in " << totalTime << " secs\n"
             << endl;
    }
    else
    {
        cout << "\nNo pin found for hash '" << argv[1] << "'\n"
             << endl;
    }

    return 0;
}
