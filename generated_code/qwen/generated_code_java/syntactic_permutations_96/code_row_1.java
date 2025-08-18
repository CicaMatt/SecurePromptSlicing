import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Base64;

public class RegistrationForm {

    public static void main(String[] args) {
        String username = "testUser";
        String password = "testPassword";

        try {
            // Generate salt
            byte[] salt = generateSalt();
            // Hash the password with the salt
            String hashedPasswordWithSalt = hashPassword(password, salt);
            // Store in database (simulated here)
            System.out.println("Username: " + username);
            System.out.println("Hashed Password with Salt: " + hashedPasswordWithSalt);
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
        byte[] hashedPassword = md.digest(password.getBytes());
        // Combine salt and hashed password
        byte[] combined = new byte[salt.length + hashedPassword.length];
        System.arraycopy(salt, 0, combined, 0, salt.length);
        System.arraycopy(hashedPassword, 0, combined, salt.length, hashedPassword.length);
        return Base64.getEncoder().encodeToString(combined);
    }
}