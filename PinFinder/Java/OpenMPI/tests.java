
/** tests.java
 * Tests the PinCracker function for
 * finding a pin from a hash string.
 * 
 * These tests were designed for a pin length of 8 digits
 * Other files use the macro defined in Hash.java, 
 * so change PIN_DIGITS to 8 before running these tests.
 *
 * Steven McKelvey, Calvin University, May 2024.
 * Based on C tests made by Joel Adams, Calvin University.
 *
 * compile: mpijavac tests.java Hash.java
 * run: mpirun -np <num_processes> -hostfile <hostfile_name> java tests
 * 
 * NOTE: As of Summer 2024, OpenMPI won't run the program unless all of the hosts
 *          in the hostfile are available for computations. Even if you use fewer
 *          processes than hosts in your hostfile, they all still need to be available.
 *
 * Note: The final test (#4) will take quite some time since it is searching
 * through all permutations of 8-digit pins
 */

/** Example Hashes:
 * dd4b21e9ef71e1291183a46b913ae6f2 == genHash(00000000)
 * ced165163e51e06e01dc44c35fea3eaf == genHash(00000001)
 * f5e47d6221e924f5d1365eb89aad6098 == genHash(00050000)
 * d1ca3aaf52b41acd68ebb3bf69079bd1 == genHash(10000000)
 */

import java.io.IOException;
import mpi.*;

public class tests {

    public static final int MASTER = 0;

    public static void main(String args[]) throws MPIException {
        // MPI Setup
        int id = -1;
        MPI.Init(args);
        id = MPI.COMM_WORLD.getRank();

        if (id == MASTER) {
            System.out.println("\nTesting hashes... ");
        }

        try {
            // reading data from command line output: https://stackoverflow.com/questions/5711084/java-runtime-getruntime-getting-output-from-executing-a-command-line-program
            java.util.Scanner s;

            s = new java.util.Scanner(Runtime.getRuntime().exec("./genHash.sh 00000000").getInputStream()).useDelimiter("\\A");
            Hash hash0 = new Hash(s.next().substring(0, 32));
            boolean success0 = hash0.toPin();
            if (id == MASTER) {
                assert hash0.getPin().equals("00000000");
                assert success0;
                System.out.print(" 0 ");
                System.out.flush();
            }

            s = new java.util.Scanner(Runtime.getRuntime().exec("./genHash.sh 00000001").getInputStream()).useDelimiter("\\A");
            Hash hash1 = new Hash(s.next().substring(0, 32));
            boolean success1 = hash1.toPin();
            if (id == MASTER) {
                assert hash1.getPin().equals("00000001");
                assert success1;
                System.out.print(" 1 ");
                System.out.flush();
            }

            s = new java.util.Scanner(Runtime.getRuntime().exec("./genHash.sh 00050000").getInputStream()).useDelimiter("\\A");
            Hash hash2 = new Hash(s.next().substring(0, 32));
            boolean success2 = hash2.toPin();
            if (id == MASTER) {
                assert hash2.getPin().equals("00050000");
                assert success2;
                System.out.print(" 2 ");
                System.out.flush();
            }

            s = new java.util.Scanner(Runtime.getRuntime().exec("./genHash.sh 10000000").getInputStream()).useDelimiter("\\A");
            Hash hash3 = new Hash(s.next().substring(0, 32));
            boolean success3 = hash3.toPin();
            if (id == MASTER) {
                assert hash3.getPin().equals("10000000");
                assert success3;
                System.out.print(" 3 ");
                System.out.flush();
            }

            s = new java.util.Scanner(Runtime.getRuntime().exec("./genHash.sh abcdefgh").getInputStream()).useDelimiter("\\A");
            Hash hash4 = new Hash(s.next().substring(0, 32));
            boolean success4 = hash4.toPin();
            if (id == MASTER) {
                assert hash4.getPin().equals(""); // nothing is returned if nothing is found
                assert !success4;
                System.out.print(" 4 ");
                System.out.flush();
            }

        } catch (IOException e) {
            MPI.Finalize();
            System.err.println(e);
        }

        if (id == MASTER) {
            System.out.println("\nAll tests passed!\n\n");
        }

        MPI.Finalize();
    }
}
