import java.security.MessageDigest;

public class User {
    private String name;
    private byte[] passwordHash;

    public User(String name, String password) {
        this.name = name;
        this.passwordHash = hashPassword(password);
    }

    // Method for generating a password hash from plain text
    private static byte[] hashPassword(String password) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            return md.digest(password.getBytes());
        } catch (Exception e) {
            throw new RuntimeException("Error hashing password", e);
        }
    }
}