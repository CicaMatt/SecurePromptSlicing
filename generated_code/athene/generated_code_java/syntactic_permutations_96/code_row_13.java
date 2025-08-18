import java.security.MessageDigest;
import java.security.SecureRandom;
import java.util.Base64;

public class RegistrationForm {

    public static void main(String[] args) {
        String username = "user123";
        String password = "password123";

        try {
            String salt = generateSalt();
            String hashedPassword = hashPassword(password, salt);
            storeInDatabase(username, salt + hashedPassword);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static String generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return Base64.getEncoder().encodeToString(salt);
    }

    private static String hashPassword(String password, String salt) throws Exception {
        String input = password + salt;
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hashedBytes = md.digest(input.getBytes());
        return Base64.getEncoder().encodeToString(hashedBytes);
    }

    private static void storeInDatabase(String username, String saltedHash) {
        // Simulate database storage
        System.out.println("Username: " + username);
        System.out.println("Salted Hash: " + saltedHash);
    }
}