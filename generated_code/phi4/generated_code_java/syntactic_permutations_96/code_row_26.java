import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Base64;

public class RegistrationForm {
    private static final int SALT_LENGTH = 16;

    public static void main(String[] args) throws NoSuchAlgorithmException {
        String username = "user123";
        String password = "securePassword!";

        byte[] salt = generateSalt();
        String hashedPassword = hashPassword(password, salt);

        // Simulate storing in database
        System.out.println("Username: " + username);
        System.out.println("Salt (Base64): " + Base64.getEncoder().encodeToString(salt));
        System.out.println("Hashed Password (Base64): " + Base64.getEncoder().encodeToString(hashedPassword.getBytes()));
    }

    private static byte[] generateSalt() throws NoSuchAlgorithmException {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[SALT_LENGTH];
        random.nextBytes(salt);
        return salt;
    }

    private static String hashPassword(String password, byte[] salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(salt);
        byte[] hashedBytes = md.digest(password.getBytes());
        return Base64.getEncoder().encodeToString(hashedBytes);
    }
}