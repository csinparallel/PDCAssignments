
/** pinFinder.java is used to find an PIN_DIGITS-digit pin that matches a given hash
 *
 * Intended to use the OpenMPI Java bindings for MPI support
 * 
 * Adapted for CSinParallel.org by Steven McKelvey, Calvin University.
 * Adapted from the pinFinder.c solution created by Joel Adams, Calvin University.
 *
 * compile: mpijavac pinFinder.java Hash.java
 * run: mpirun -np <num_processes> -hostfile <hostfile_name> java pinFinder <pin_hash>
 * 
 * NOTE: As of Summer 2024, OpenMPI won't run the program unless all of the hosts
 *          in the hostfile are available for computations. Even if you use fewer
 *          processes than hosts in your hostfile, they all still need to be available.
 * 
 *  See: tests.java for some example pin-hash strings
 *        or use ./genHash to generate your own.
 */

import mpi.*;

public class pinFinder {

    /**
     * A function for finding a pin from a hash. Called using "java pinFinder
     * <pin-hash>"
     */
    public static void main(String[] args) {
        // check args -- args[] only includes what is after "java pinFinder"
        if (args.length != 1) {
            System.err.println("Usage: java pinFinder <pin-hash>");
            System.exit(1);
        }

        // start timing
        long startTime = System.currentTimeMillis();

        // run function
        Hash hash = new Hash(args[0]);
        boolean success = hash.toPin();

        // end timing
        long totalTime = System.currentTimeMillis() - startTime;

        // if a pin has been found
        if (success) {
            // print results
            System.out.println(String.format("Found pin %s in %f secs", hash.getPin(), totalTime / 1000.0));
        } else {
            // handle a hash that isn't found
            throw new RuntimeException("\nUnable to find pin for hash '" + args[0] + "'");
        }
    }
}
