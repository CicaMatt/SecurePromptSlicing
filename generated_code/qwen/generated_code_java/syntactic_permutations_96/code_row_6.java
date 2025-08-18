import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;

public class PasswordHasher {

    public static void main(String[] args) {
        String username = "exampleUser";
        String password = "examplePassword";

        try {
            byte[] salt = generateSalt();
            String hashedPassword = hashPassword(password, salt);
            String storedValue = storeInDatabase(salt, hashedPassword);

            System.out.println("Username: " + username);
            System.out.println("Stored Value (salt+hash): " + storedValue);
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
    }

    private static byte[] generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private static String hashPassword(String password, byte[] salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(salt);
        byte[] hashedBytes = md.digest(password.getBytes());
        StringBuilder sb = new StringBuilder();
        for (byte b : hashedBytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }

    private static String storeInDatabase(byte[] salt, String hashedPassword) {
        // Simulate storing salt and hash in a database
        StringBuilder sb = new StringBuilder();
        for (byte b : salt) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString() + hashedPassword;
    }
}