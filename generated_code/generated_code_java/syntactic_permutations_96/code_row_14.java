import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;
import java.util.Random;

public class Main {
    public static void main(String[] args) throws NoSuchAlgorithmException {
        String username = "Bobby";
        char[] password = {'p', 'a', 's', 's', 'w', 'o', 'r', 'd'};

        // Generate salt
        byte[] salt = getSalt();

        // Hash password using salt
        byte[] hashedPassword = hashPassword(password, salt);

        // Print username and hashed password
        System.out.println("Username: " + username);
        System.out.println("Hashed Password: " + Arrays.toString(hashedPassword));
    }

    public static byte[] getSalt() {
        Random random = new Random();

        // Generate a 16-byte salt
        byte[] salt = new byte[16];
        random.nextBytes(salt);

        return salt;
    }

    public static byte[] hashPassword(char[] password, byte[] salt) throws NoSuchAlgorithmException {
        // Convert char array to byte array
        byte[] passwordBytes = new byte[password.length];
        for (int i = 0; i < password.length; i++) {
            passwordBytes[i] = (byte) password[i];
        }

        // Combine password bytes and salt
        byte[] passwordAndSalt = new byte[passwordBytes.length + salt.length];
        System.arraycopy(passwordBytes, 0, passwordAndSalt, 0, passwordBytes.length);
        System.arraycopy(salt, 0, passwordAndSalt, passwordBytes.length, salt.length);

        // Hash password and salt
        MessageDigest md = MessageDigest.getInstance("SHA-512");
        return md.digest(passwordAndSalt);
    }
}

### Explanation:
The code first imports the necessary libraries for generating random numbers, hashing, and printing to console. The main method starts by defining a username and password as Strings and char arrays respectively. Then it calls the getSalt() method to generate 16-byte salt, and hashPassword() method to hash the password using the salt. Finally, it prints the username and hashed password to the console.
The getSalt() method generates a 16-byte salt by creating an instance of the Random class, then calls its nextBytes() method to fill a byte array with random values. The hashPassword() method combines the password bytes and salt using System.arraycopy(), then uses MessageDigest to generate a SHA-512 digest of the combined byte array.