import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;

public class RegistrationForm {

    private static final int SALT_LENGTH = 16;

    public static void main(String[] args) {
        String username = "testUser";
        String password = "securePassword";

        byte[] salt = generateSalt();
        String hashedPasswordWithSalt = hashPassword(password, salt);

        // Simulate storing in a database
        System.out.println("Username: " + username);
        System.out.println("Salt: " + bytesToHex(salt));
        System.out.println("Hashed Password with Salt: " + hashedPasswordWithSalt);
    }

    private static byte[] generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[SALT_LENGTH];
        random.nextBytes(salt);
        return salt;
    }

    private static String hashPassword(String password, byte[] salt) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            md.update(salt);
            byte[] hashedPassword = md.digest(password.getBytes());
            return bytesToHex(hashedPassword);
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }

    private static String bytesToHex(byte[] bytes) {
        StringBuilder sb = new StringBuilder();
        for (byte b : bytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }
}