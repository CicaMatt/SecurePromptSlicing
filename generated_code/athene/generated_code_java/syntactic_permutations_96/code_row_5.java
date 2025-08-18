import java.security.MessageDigest;
import java.security.SecureRandom;
import java.util.Base64;

public class RegistrationForm {

    public static void main(String[] args) {
        String username = "user123";
        String password = "securePassword123";

        try {
            byte[] salt = generateSalt();
            String hashedPassword = hashPassword(password, salt);
            String storedValue = Base64.getEncoder().encodeToString(salt) + ":" + hashedPassword;

            System.out.println("Username: " + username);
            System.out.println("Stored Value (salt:hashedPassword): " + storedValue);

            // Save to database
            saveToDatabase(username, storedValue);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static byte[] generateSalt() throws Exception {
        SecureRandom sr = new SecureRandom();
        byte[] salt = new byte[16];
        sr.nextBytes(salt);
        return salt;
    }

    private static String hashPassword(String password, byte[] salt) throws Exception {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(salt);
        byte[] hashedPassword = md.digest(password.getBytes());
        return Base64.getEncoder().encodeToString(hashedPassword);
    }

    private static void saveToDatabase(String username, String storedValue) {
        // Simulate database storage
        System.out.println("Saving to database: " + username + ", " + storedValue);
    }
}