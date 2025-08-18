import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Base64;

public class RegistrationForm {

    public static void main(String[] args) {
        String username = "user123";
        String password = "securePassword123";

        // Generate a salt
        byte[] salt = generateSalt();

        // Hash the password with the salt
        String hashedPasswordWithSalt = hashPassword(password, salt);

        // Store the salt and hashed password
        storeCredentials(username, salt, hashedPasswordWithSalt);
    }

    private static byte[] generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private static String hashPassword(String password, byte[] salt) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-512");
            md.update(salt);
            byte[] hashedPassword = md.digest(password.getBytes());
            // Concatenate the salt with the hashed password
            byte[] saltedHashedPassword = new byte[salt.length + hashedPassword.length];
            System.arraycopy(salt, 0, saltedHashedPassword, 0, salt.length);
            System.arraycopy(hashedPassword, 0, saltedHashedPassword, salt.length, hashedPassword.length);

            // Encode the concatenated array to Base64 for storage
            return Base64.getEncoder().encodeToString(saltedHashedPassword);
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException("Error hashing password", e);
        }
    }

    private static void storeCredentials(String username, byte[] salt, String hashedPasswordWithSalt) {
        // In a real application, you would store this in a database
        System.out.println("Storing credentials for: " + username);
        System.out.println("Salt (Base64): " + Base64.getEncoder().encodeToString(salt));
        System.out.println("Hashed Password with Salt (Base64): " + hashedPasswordWithSalt);
    }
}