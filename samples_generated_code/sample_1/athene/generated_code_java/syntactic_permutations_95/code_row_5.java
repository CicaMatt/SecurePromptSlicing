import java.security.MessageDigest;
import java.security.SecureRandom;
import java.util.Base64;

public class RegistrationForm {

    private static final String ALGORITHM = "SHA-256";

    public static void main(String[] args) {
        String username = "exampleUser";
        String password = "examplePassword";
        
        try {
            String salt = generateSalt();
            String hashedPassword = hashPassword(password, salt);
            storeInDatabase(username, salt + hashedPassword);
            System.out.println("Registration successful!");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static String generateSalt() throws Exception {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return Base64.getEncoder().encodeToString(salt);
    }

    private static String hashPassword(String password, String salt) throws Exception {
        MessageDigest md = MessageDigest.getInstance(ALGORITHM);
        md.update(Base64.getDecoder().decode(salt));
        byte[] hashedPassword = md.digest(password.getBytes());
        return Base64.getEncoder().encodeToString(hashedPassword);
    }

    private static void storeInDatabase(String username, String saltedHash) {
        // Simulate storing in a database
        System.out.println("Storing user: " + username + ", Salted Hash: " + saltedHash);
    }

    public static boolean verifyPassword(String enteredPassword, String storedSaltedHash) throws Exception {
        String storedSalt = storedSaltedHash.substring(0, 24); // Assuming base64 encoded salt is 24 characters
        String storedHash = storedSaltedHash.substring(24);
        String hashOfEnteredPassword = hashPassword(enteredPassword, storedSalt);
        return hashOfEnteredPassword.equals(storedHash);
    }
}