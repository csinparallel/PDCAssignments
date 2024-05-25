/** tests.java
 * Tests the PinCracker function for
 * finding a pin from a hash string.
 * 
 * Steven McKelvey, Calvin University, May 2024.
 * Based on C tests made by Joel Adams, Calvin University.
 * 
 * compile: javac -deprecation tests.java
 * run: java tests
 * 
 * Note: The final test (#4) will take quite some 
 *      time since it is searching through all 
 *      permutations of 8-digit pins
 */

import java.io.IOException;

public class tests {
    public static void main(String args[]) {
        pinFinder pf = new pinFinder();

        System.out.println("\nTesting hashes... ");
        
        try {
            // https://stackoverflow.com/questions/5711084/java-runtime-getruntime-getting-output-from-executing-a-command-line-program
            java.util.Scanner s;
            String result;

            s = new java.util.Scanner(Runtime.getRuntime().exec("./genHash.sh 00000000").getInputStream()).useDelimiter("\\A");
            result = pf.findPinFromHash( s.next().substring(0,32) );
            assert result.equals("00000000");
            System.out.print(" 0 "); System.out.flush();
            
            s = new java.util.Scanner(Runtime.getRuntime().exec("./genHash.sh 00000001").getInputStream()).useDelimiter("\\A");
            result = pf.findPinFromHash( s.next().substring(0,32) );
            assert result.equals("00000001");
            System.out.print(" 1 "); System.out.flush();

            s = new java.util.Scanner(Runtime.getRuntime().exec("./genHash.sh 00050000").getInputStream()).useDelimiter("\\A");
            result = pf.findPinFromHash( s.next().substring(0,32) );
            assert result.equals("00050000");
            System.out.print(" 2 "); System.out.flush();

            s = new java.util.Scanner(Runtime.getRuntime().exec("./genHash.sh 10000000").getInputStream()).useDelimiter("\\A");
            result = pf.findPinFromHash( s.next().substring(0,32) );
            assert result.equals("10000000");
            System.out.print(" 3 "); System.out.flush();

            s = new java.util.Scanner(Runtime.getRuntime().exec("./genHash.sh abcdefgh").getInputStream()).useDelimiter("\\A");
            result = pf.findPinFromHash( s.next().substring(0,32) );
            assert result == null; // nothing is returned if nothing is found
            System.out.print(" 4 "); System.out.flush();

        } catch (IOException e) {
            System.err.println(e);
        }
        
        System.out.println("\nAll tests passed!\n\n");


    }
}