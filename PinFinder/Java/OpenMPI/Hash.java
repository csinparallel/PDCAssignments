
/** Hash.java
 * Defines a Hash class that:
 * - Stores a 32-character MD5 hash string and (once decoded) its corresponding pin
 * - finds (and stores) a corresponding pin to a given hash using toPin()
 *
 * Adapted for CSinParallel.org by Steven McKelvey, Calvin University.
 * Adapted from the pinFinder.c solution created by Joel Adams, Calvin University.
 */

import mpi.*;
import java.nio.CharBuffer;
// packages for MD5 hashing
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

import java.lang.Math; // pow()

public class Hash {
    public static final int PIN_DIGITS = 8; // constant for the length of a pin
    public static final int PIN_BUF_SIZE = PIN_DIGITS+1;

    private final String hash;
    private String pin = "";

    /**
     * Constructor
     * @param usersHash: the hash to be decoded
     */
    public Hash(final String usersHash) {
        this.hash = usersHash;
    }

    public String getPin() {
        return pin;
    }

    public String getHash() {
        return hash;
    }

    /**
     * testable brute force method to find an PIN_DIGITS-digit pin, given its hash
     *
     * @param: usersHash, the hash of the pin being recovered.
     * @pre usersHash contains the MD5 hash of an PIN_DIGITS-digit pin
     * @return the pin that was used to compute the input hash
     */
    public boolean toPin() {
        int i = 0;
        String num, currentHash = "";

        while (i < Math.pow(10, PIN_DIGITS)) {
            // go from num i -> string pin (of format "00000000")
            // pad left with 0s, width of PIN_DIGITS, i = integer 
            num = String.format("%0" + PIN_DIGITS + "d", i);

            // hash that pin
            currentHash = hashUsingMD5(num);

            // compare that pin to the usersHash and return if the pin has been found
            if (hash.equals(currentHash)) {
                pin = num;      // store the found pin
                return true;    // return success
            }

            // increment otherwise
            ++i;
        }
        return false; // nothing found
    }

    /**
     * compute the hash of the current number-string.
     *
     * @param: currentString, an PIN_DIGITS-digit string of the num (pin) we are
     * currently trying.
     * @return A hash of the input pin (currentString)
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
            for (int i = 0; i < 16; ++i) {
                hash += String.format("%02x", digest[i]);
            }
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
        return hash;
    }
}
