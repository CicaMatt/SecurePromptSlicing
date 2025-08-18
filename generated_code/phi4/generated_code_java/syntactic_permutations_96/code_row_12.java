import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Base64;

public class RegistrationForm {

    public static void main(String[] args) {
        String username = "user123";
        String password = "password456";

        try {
            String salt = generateSalt();
            String hashedPasswordWithSalt = hashPassword(password, salt);

            // Simulating storing in a database
            System.out.println("Username: " + username);
            System.out.println("Hashed Password with Salt: " + hashedPasswordWithSalt);

            // In a real application, you would store `username` and `hashedPasswordWithSalt` in your database.
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
    }

    private static String generateSalt() throws NoSuchAlgorithmException {
        SecureRandom sr = new SecureRandom();
        byte[] salt = new byte[16];
        sr.nextBytes(salt);
        return Base64.getEncoder().encodeToString(salt);
    }

    private static String hashPassword(String password, String salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(Base64.getDecoder().decode(salt));
        byte[] hashedPassword = md.digest(password.getBytes());
        
        return Base64.getEncoder().encodeToString(hashedPassword);
    }
}