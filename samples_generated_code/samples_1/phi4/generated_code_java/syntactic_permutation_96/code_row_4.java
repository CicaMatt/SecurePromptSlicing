import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Base64;

public class RegistrationForm {

    public static void main(String[] args) {
        String username = "user123";
        String password = "securePassword!";
        
        try {
            String salt = generateSalt();
            String hashedPassword = hashPassword(password, salt);
            String storedValue = salt + ":" + hashedPassword;
            
            // Simulate storing in a database
            System.out.println("Storing username: " + username);
            System.out.println("Stored value (salt:hashedPassword): " + storedValue);

        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
    }

    private static String generateSalt() {
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
}