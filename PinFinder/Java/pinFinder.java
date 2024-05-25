/** pinFinder.java is used to find an 8-digit pin that matches a given hash 
 * 
 * Adapted for CSinParallel.org by Steven McKelvey, Calvin University. 
 * Adapted from the pinFinder.c solution created by Joel Adams, Calvin University.
 * 
 * compile: javac -deprecation pinFinder.java
 * run: java pinFinder <pin-hash>
 */

// packages for MD5 hashing
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class pinFinder {
    /** A function for finding a pin from a hash.
     *  Called using "java pinFinder <pin-hash>"
     */
    public static void main(String [] args) {
        // check args -- args[] only includes what is after "java pinFinder"
        if (args.length != 1) {
            System.err.println("Usage: java pinFinder <pin-hash>");
            System.exit(1);
        }
        // start timing
        long startTime = System.currentTimeMillis();

        // run func
        String pin = findPinFromHash(args[0]);

        // end timing
        long totalTime = System.currentTimeMillis() - startTime;

        // if a pin has been found
        if (pin != null) {
            // print results
            System.out.println(String.format("Found pin %s in %f secs", pin, totalTime / 1000.0));
        } else {
            // handle a hash that isn't found
            throw new RuntimeException("\nUnable to find pin for hash '" + args[0] + "'");
        }

    }

    /** testable brute force method to find an 8-digit pin, given its hash
     *  @param: usersHash, the hash of the pin being recovered.
     *  PRE: usersHash contains the MD5 hash of an 8-digit pin
     *  RETURN: the pin that was used to compute the input hash
     */ 
    public static String findPinFromHash(String usersHash) {
        final int PIN_LENGTH = 8;
        final int PIN_BOUND = 100000000;
        int i = 0;
        String num, currentHash = "";
        while (i < PIN_BOUND) {
            // go from num i -> string pin (of format "00000000")
                // pad left with 0s, width of PIN_LENGTH, i = integer 
            num = String.format("%0" + PIN_LENGTH + "d", i);
            
            // hash that pin
            currentHash = hashUsingMD5(num);

            // compare that pin to the usersHash and return if the pin has been found
            if (usersHash.equals(currentHash)) return num;

            // increment otherwise
            i++;
        }
        return null; // nothing found
    }

    /** compute the hash of the current number-string.
     *  @param: currentString, an 8-digit string of the num (pin) we are currently trying.
     *  RETURN: A hash of the input pin (currentString)
     */
    private static String hashUsingMD5(String currentString) {
        String hash = "";
        String addition;
        try {
            // https://www.baeldung.com/java-md5
            MessageDigest md = MessageDigest.getInstance("MD5"); // use MD5 algorithm
            md.update(currentString.getBytes());
            byte[] digest = md.digest();
            
            // convert hash (digest) to base-16 string
            for (int i = 0; i < 16; i++) {
                hash += String.format("%02x", digest[i]);
            }
        } catch(NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
        return hash;
    }
}