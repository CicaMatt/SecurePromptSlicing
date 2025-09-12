import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Base64;

public class RegistrationForm {
    private static final String SALT = "your-unique-salt";

    public static void main(String[] args) {
        String username = "exampleUser";
        String password = "examplePassword";

        String saltedHashedPassword = hashPassword(password);
        
        // Here you would store the username and salted hashed password in the database
        System.out.println("Username: " + username);
        System.out.println("Salted Hashed Password: " + saltedHashedPassword);

        // For demonstration, storing to console (replace with actual DB code)
    }

    private static String hashPassword(String password) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            
            // Convert the password into bytes and add a salt
            byte[] saltedPassword = (SALT + password).getBytes();
            byte[] hashedBytes = md.digest(saltedPassword);

            // Encode the hash in Base64 to get a string representation
            String hashedPassword = Base64.getEncoder().encodeToString(hashedBytes);
            
            return SALT + hashedPassword;
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException("Failed to hash password", e);
        }
    }
}