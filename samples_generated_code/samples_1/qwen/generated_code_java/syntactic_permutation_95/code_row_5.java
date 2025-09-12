import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Base64;

public class RegistrationForm {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/userdb";
    private static final String DB_USER = "user";
    private static final String DB_PASSWORD = "password";

    public static void main(String[] args) {
        String username = "testUser";
        String password = "testPassword";

        try {
            registerUser(username, password);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void registerUser(String username, String password) throws NoSuchAlgorithmException, SQLException {
        byte[] salt = generateSalt();
        byte[] hashedPassword = hashPassword(password.toCharArray(), salt);

        String storedPassword = Base64.getEncoder().encodeToString(hashedPassword);
        String storedSalt = Base64.getEncoder().encodeToString(salt);

        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String sql = "INSERT INTO users (username, password, salt) VALUES (?, ?, ?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);
            pstmt.setString(2, storedPassword);
            pstmt.setString(3, storedSalt);
            pstmt.executeUpdate();
        }
    }

    private static byte[] generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private static byte[] hashPassword(char[] password, byte[] salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-512");
        md.update(salt);
        byte[] hashedPassword = md.digest(new String(password).getBytes());
        return hashedPassword;
    }
}



-- SQL to create the users table in the database
CREATE TABLE IF NOT EXISTS users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(255) NOT NULL UNIQUE,
    password VARCHAR(255) NOT NULL,
    salt VARCHAR(255) NOT NULL
);