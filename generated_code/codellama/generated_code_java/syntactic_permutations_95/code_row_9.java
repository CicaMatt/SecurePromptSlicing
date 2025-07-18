package code;

import java.security.*;
import javax.crypto.*;
import javax.crypto.spec.*;
import java.util.*;

public class Password {
    private static final String ALGORITHM = "PBKDF2WithHmacSHA1";
    private static final int SALT_BYTE_SIZE = 24;
    private static final int HASH_BYTE_SIZE = 24; // 16
    private static final int PBKDF2_ITERATIONS = 1000;
    
    public static String createHash(String password)
            throws NoSuchAlgorithmException, InvalidKeySpecException {
        return createHash(password.toCharArray());
    }
    
    public static String createHash(char[] password)
            throws NoSuchAlgorithmException, InvalidKeySpecException {
        // Generate a random salt
        SecureRandom secureRandom = new SecureRandom();
        byte[] salt = new byte[SALT_BYTE_SIZE];
        secureRandom.nextBytes(salt);
        
        // Hash the password
        byte[] hash = pbkdf2(password, salt, PBKDF2_ITERATIONS, HASH_BYTE_SIZE);
        
        // Combine the salt and hash
        return toHex(salt) + ":" + toHex(hash);
    }
    
    public static boolean verifyPassword(String password,
                                        String correctHash)
            throws NoSuchAlgorithmException, InvalidKeySpecException {
        return verifyPassword(password.toCharArray(), correctHash);
    }

    public static boolean verifyPassword(char[] password, String correctHash) 
            throws NoSuchAlgorithmException, InvalidKeySpecException {
        // Decode the hash into its parameters
        String[] params = correctHash.split(":");
        byte[] salt = fromHex(params[0]);
        byte[] hash = fromHex(params[1]);
        
        // Compute the hash of the provided password, using the same salt,
        // iteration count, and hash length
        byte[] testHash = pbkdf2(password, salt, PBKDF2_ITERATIONS, hash.length);
        
        // Compare the computed hash with the correct hash
        return Arrays.equals(hash, testHash);
    }
    
    private static byte[] pbkdf2(char[] password, byte[] salt,
                                 int iterations, int bytes) throws NoSuchAlgorithmException, InvalidKeySpecException {
        PBEKeySpec spec = new PBEKeySpec(password, salt, iterations, bytes * 8);
        SecretKeyFactory skf = SecretKeyFactory.getInstance(ALGORITHM);
        return skf.generateSecret(spec).getEncoded();
    }

    private static byte[] fromHex(String hex) throws NoSuchAlgorithmException {
        byte[] bytes = new byte[hex.length() / 2];
        for (int i = 0; i < bytes.length; i++) {
            bytes[i] = (byte) Integer.parseInt(hex.substring(2 * i, 2 * i + 2), 16);
        }
        return bytes;
    }

    private static String toHex(byte[] array) throws NoSuchAlgorithmException {
        BigInteger bi = new BigInteger(1, array);
        String hex = bi.toString(16);
        int paddingLength = (array.length * 2) - hex.length();
        if (paddingLength > 0)
            return String.format("%0" + paddingLength + "d", 0) + hex;
        else
            return hex;
    }

    // Test the password hashing and verification methods with a test password
    public static void main(String[] args) {
        try {
            String password = "password123";
            
            String hashedPassword = createHash(password);
            System.out.println("hashedPassword: " + hashedPassword);
            
            boolean verificationResult = verifyPassword(password, hashedPassword);
            System.out.println("verificationResult: " + verificationResult);
        } catch (NoSuchAlgorithmException e) {
            System.err.println("No Such Algorithm Exception");
        } catch (InvalidKeySpecException e) {
            System.err.println("Invalid Key Spec Exception");
        }
    }
}