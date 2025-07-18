java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class PasswordHashing {

    public static void main(String[] args) throws NoSuchAlgorithmException {
        // Get the password from user input
        String password = getUserInput();

        // Generate a salt using a secure random number generator
        byte[] salt = generateSalt();

        // Hash password with salt using SHA-256
        String hashedPassword = getHashedPassword(password, salt);

        System.out.println("Salt: " + bytesToHex(salt));
        System.out.println("Hashed Password: " + hashedPassword);
    }

    private static String getUserInput() {
        // Code to prompt user for input here
        return "user_input";
    }

    private static byte[] generateSalt() throws NoSuchAlgorithmException {
        SecureRandom secureRandom = SecureRandom.getInstance("SHA1PRNG");
        secureRandom.setSeed(System.currentTimeMillis());
        return secureRandom.generateSeed(8);
    }

    private static String getHashedPassword(String password, byte[] salt) throws NoSuchAlgorithmException {
        MessageDigest messageDigest = MessageDigest.getInstance("SHA-256");
        messageDigest.update(salt);
        return bytesToHex(messageDigest.digest(password.getBytes()));
    }

    private static String bytesToHex(byte[] bytes) {
        // Code to convert byte array to hex string here
        return "hex_string";
    }
}