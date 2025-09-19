import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Base64;

public class RegistrationForm {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/registrationdb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        registerUser("testuser", "securePassword123");
    }

    public static void registerUser(String username, String password) {
        byte[] salt = generateSalt();
        String hashedPasswordWithSalt = hashPassword(password, salt);

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)")) {

            pstmt.setString(1, username);
            pstmt.setString(2, Base64.getEncoder().encodeToString(hashedPasswordWithSalt));
            pstmt.executeUpdate();

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static byte[] generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private static String hashPassword(String password, byte[] salt) {
        MessageDigest md;
        try {
            md = MessageDigest.getInstance("SHA-512");
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
        md.update(salt);
        byte[] hashedPassword = md.digest(password.getBytes());
        byte[] hashedPasswordWithSalt = new byte[hashedPassword.length + salt.length];
        System.arraycopy(hashedPassword, 0, hashedPasswordWithSalt, 0, hashedPassword.length);
        System.arraycopy(salt, 0, hashedPasswordWithSalt, hashedPassword.length, salt.length);
        return Base64.getEncoder().encodeToString(hashedPasswordWithSalt);
    }
}