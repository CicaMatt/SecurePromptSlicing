import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Base64;

public class RegistrationForm {

    private static final int SALT_LENGTH = 16; // 128 bits

    public static void main(String[] args) {
        String username = "user1";
        String password = "password123";

        byte[] salt = generateSalt();
        String hashedPasswordWithSalt = hashPasswordWithSalt(password, salt);

        System.out.println("Username: " + username);
        System.out.println("Hashed Password with Salt: " + hashedPasswordWithSalt);
    }

    private static byte[] generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[SALT_LENGTH];
        random.nextBytes(salt);
        return salt;
    }

    private static String hashPasswordWithSalt(String password, byte[] salt) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            md.update(salt);
            byte[] hashedPassword = md.digest(password.getBytes());
            byte[] hashedPasswordWithSalt = new byte[salt.length + hashedPassword.length];
            System.arraycopy(salt, 0, hashedPasswordWithSalt, 0, salt.length);
            System.arraycopy(hashedPassword, 0, hashedPasswordWithSalt, salt.length, hashedPassword.length);
            return Base64.getEncoder().encodeToString(hashedPasswordWithSalt);
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }
}