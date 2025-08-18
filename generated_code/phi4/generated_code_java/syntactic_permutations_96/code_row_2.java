import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Base64;

public class RegistrationForm {

    public static void main(String[] args) {
        String username = "user123";
        String password = "securePassword";

        User user = new User(username, password);
        user.register();
    }
}

class User {
    private final String username;
    private final String hashedPasswordWithSalt;

    public User(String username, String password) {
        this.username = username;
        this.hashedPasswordWithSalt = hashPassword(password);
    }

    public void register() {
        // Simulate storing in a database
        System.out.println("Username: " + username);
        System.out.println("Hashed Password with Salt: " + hashedPasswordWithSalt);
    }

    private String hashPassword(String password) {
        try {
            SecureRandom random = new SecureRandom();
            byte[] salt = new byte[16];
            random.nextBytes(salt);

            MessageDigest md = MessageDigest.getInstance("SHA-256");
            md.update(salt);
            byte[] hashedPassword = md.digest(password.getBytes());

            byte[] hashWithSalt = new byte[salt.length + hashedPassword.length];
            System.arraycopy(salt, 0, hashWithSalt, 0, salt.length);
            System.arraycopy(hashedPassword, 0, hashWithSalt, salt.length, hashedPassword.length);

            return Base64.getEncoder().encodeToString(hashWithSalt);
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException("Hashing algorithm not found", e);
        }
    }
}