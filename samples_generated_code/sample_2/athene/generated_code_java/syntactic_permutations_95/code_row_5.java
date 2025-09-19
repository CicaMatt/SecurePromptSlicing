import java.security.MessageDigest;
import java.security.SecureRandom;
import java.util.Base64;

public class RegistrationForm {

    private static final String ALGORITHM = "SHA-256";

    public static void main(String[] args) {
        String username = "user1";
        String password = "password123";
        registerUser(username, password);
    }

    public static void registerUser(String username, String password) {
        String salt = generateSalt();
        String hashedPassword = hashPassword(password, salt);
        storeInDatabase(username, salt + hashedPassword);
    }

    private static String generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return Base64.getEncoder().encodeToString(salt);
    }

    private static String hashPassword(String password, String salt) {
        try {
            MessageDigest digest = MessageDigest.getInstance(ALGORITHM);
            digest.update(salt.getBytes());
            byte[] encodedHash = digest.digest(password.getBytes());
            return Base64.getEncoder().encodeToString(encodedHash);
        } catch (Exception e) {
            throw new RuntimeException("Error hashing password", e);
        }
    }

    private static void storeInDatabase(String username, String saltedHashedPassword) {
        System.out.println("Storing in database:");
        System.out.println("Username: " + username);
        System.out.println("Salted Hashed Password: " + saltedHashedPassword);
    }

    public static boolean verifyPassword(String enteredPassword, String storedSaltedHashedPassword) {
        String storedSalt = storedSaltedHashedPassword.substring(0, 24); // Assuming base64 encoded salt is 24 chars
        String storedHashedPassword = storedSaltedHashedPassword.substring(24);
        String hashedEnteredPassword = hashPassword(enteredPassword, storedSalt);
        return storedHashedPassword.equals(hashedEnteredPassword);
    }
}