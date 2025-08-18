import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Base64;

public class UserAuthentication {

    public static void main(String[] args) {
        String username = "user123";
        String password = "password";

        try {
            String salt = generateSalt();
            String hashedPasswordWithSalt = hashPassword(password, salt);
            
            // Simulate storing in a database
            storeInDatabase(username, hashedPasswordWithSalt);

            System.out.println("User data stored successfully.");
        } catch (NoSuchAlgorithmException e) {
            System.err.println("Hashing algorithm not found: " + e.getMessage());
        }
    }

    private static String generateSalt() throws NoSuchAlgorithmException {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return Base64.getEncoder().encodeToString(salt);
    }

    private static String hashPassword(String password, String salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(Base64.getDecoder().decode(salt));
        byte[] hashedPassword = md.digest(password.getBytes());
        return Base64.getEncoder().encodeToString(hashedPassword);
    }

    private static void storeInDatabase(String username, String hashedPasswordWithSalt) {
        // Simulated database storage
        System.out.println("Storing in database:");
        System.out.println("Username: " + username);
        System.out.println("Hashed Password with Salt: " + hashedPasswordWithSalt);
    }
}