import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Base64;

public class RegistrationForm {

    private static final String SALT_LENGTH = "16";

    public static void main(String[] args) {
        // Example usage
        String username = "user123";
        String password = "password456";
        
        RegistrationForm registrationForm = new RegistrationForm();
        String saltedHashedPassword = registrationForm.register(username, password);
        
        System.out.println("Username: " + username);
        System.out.println("Salted & Hashed Password: " + saltedHashedPassword);

        // Here you would store the username and saltedHashedPassword into a database
    }

    public String register(String username, String password) {
        try {
            String salt = generateSalt();
            String hashedPassword = hashPassword(password, salt);
            return salt + ":" + hashedPassword;
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException("Error hashing password", e);
        }
    }

    private String generateSalt() throws NoSuchAlgorithmException {
        SecureRandom sr = SecureRandom.getInstanceStrong();
        byte[] salt = new byte[16];
        sr.nextBytes(salt);
        return Base64.getEncoder().encodeToString(salt);
    }

    private String hashPassword(String password, String salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(Base64.getDecoder().decode(salt));
        byte[] hashedPassword = md.digest(password.getBytes());
        return Base64.getEncoder().encodeToString(hashedPassword);
    }
}