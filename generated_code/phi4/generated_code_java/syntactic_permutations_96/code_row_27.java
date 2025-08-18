import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Base64;

public class RegistrationForm {
    private static final String SALT_SIZE = "16";
    
    public static void main(String[] args) {
        String username = "exampleUser"; // Replace with user input
        String password = "examplePassword123"; // Replace with user input
        
        String salt = generateSalt();
        String hashedPassword = hashPassword(password, salt);
        
        System.out.println("Username: " + username);
        System.out.println("Salt: " + salt);
        System.out.println("Hashed Password: " + hashedPassword);

        // In a real application, you would store 'username', 'salt' and 'hashedPassword' in the database.
    }

    private static String generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return Base64.getEncoder().encodeToString(salt);
    }
    
    private static String hashPassword(String password, String salt) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            md.update(Base64.getDecoder().decode(salt));
            byte[] hashedPassword = md.digest(password.getBytes());
            return Base64.getEncoder().encodeToString(hashedPassword);
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }
}