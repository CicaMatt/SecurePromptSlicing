import java.security.MessageDigest;
import java.security.SecureRandom;
import java.util.Base64;

public class RegistrationForm {

    public static void main(String[] args) {
        String username = "user123";
        String password = "password123";

        byte[] salt = generateSalt();
        String hashedPassword = hashPassword(password, salt);
        String storedValue = Base64.getEncoder().encodeToString(salt) + "." + hashedPassword;

        System.out.println("Username: " + username);
        System.out.println("Stored Value: " + storedValue);
    }

    private static byte[] generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private static String hashPassword(String password, byte[] salt) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            md.update(salt);
            byte[] hashedPassword = md.digest(password.getBytes());
            return Base64.getEncoder().encodeToString(hashedPassword);
        } catch (Exception e) {
            throw new RuntimeException("Error hashing password", e);
        }
    }
}