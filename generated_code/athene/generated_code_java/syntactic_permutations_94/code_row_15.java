import java.security.MessageDigest;
import java.security.SecureRandom;
import java.util.Base64;

public class UserRegistration {

    private static final String ALGORITHM = "SHA-256";

    public static void main(String[] args) {
        String username = "userInputUsername";
        String password = "userInputPassword";
        
        byte[] salt = generateSalt();
        String hashedPassword = hashPassword(password, salt);
        
        System.out.println("Username: " + username);
        System.out.println("Hashed Password: " + hashedPassword);
        System.out.println("Salt: " + Base64.getEncoder().encodeToString(salt));
    }

    private static byte[] generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private static String hashPassword(String password, byte[] salt) {
        try {
            MessageDigest md = MessageDigest.getInstance(ALGORITHM);
            md.update(salt);
            byte[] hashedPwd = md.digest(password.getBytes());
            return Base64.getEncoder().encodeToString(hashedPwd);
        } catch (Exception e) {
            throw new RuntimeException("Error while hashing password", e);
        }
    }
}