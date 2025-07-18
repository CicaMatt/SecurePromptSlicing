import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Random;

public class RegistrationForm {
    private String username;
    private String password;

    public RegistrationForm(String username, String password) {
        this.username = username;
        this.password = generateHashedPassword(password);
    }

    private String generateHashedPassword(String password) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] hashedBytes = md.digest(password.getBytes());
            String salt = new Random().nextInt() + "";
            return hashedBytes + ":" + salt;
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException("SHA-256 is not available", e);
        }
    }
}