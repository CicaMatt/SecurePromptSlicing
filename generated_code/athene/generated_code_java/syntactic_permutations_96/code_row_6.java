import java.security.MessageDigest;
import java.security.SecureRandom;
import java.util.Base64;

public class PasswordHashing {
    public static void main(String[] args) {
        String username = "user1";
        String password = "password123";
        
        String salt = generateSalt();
        String hashedPassword = hashPassword(password, salt);
        
        String storedInDatabase = username + ":" + Base64.getEncoder().encodeToString(salt.getBytes()) + ":" + hashedPassword;
        System.out.println(storedInDatabase);
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
            byte[] hashed = md.digest(password.getBytes());
            return Base64.getEncoder().encodeToString(hashed);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}