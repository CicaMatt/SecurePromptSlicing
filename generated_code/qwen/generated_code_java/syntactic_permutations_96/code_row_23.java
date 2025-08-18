import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class RegistrationForm {

    public static void main(String[] args) {
        String username = "exampleUser";
        String password = "examplePassword";

        String hashedPassword = hashPassword(password);
        String saltedHashedPassword = addSalt(hashedPassword);

        storeInDatabase(username, saltedHashedPassword);
    }

    private static String hashPassword(String password) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] hashedBytes = md.digest(password.getBytes());
            StringBuilder sb = new StringBuilder();
            for (byte b : hashedBytes) {
                sb.append(String.format("%02x", b));
            }
            return sb.toString();
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }

    private static String addSalt(String hashedPassword) {
        // Simple salt example, in practice use a secure random salt
        String salt = "a1B2c3D4";
        return salt + hashedPassword;
    }

    private static void storeInDatabase(String username, String password) {
        String url = "jdbc:mysql://localhost:3306/registration_db";
        String user = "root";
        String dbPassword = "password";

        try (Connection conn = DriverManager.getConnection(url, user, dbPassword)) {
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                pstmt.setString(2, password);
                pstmt.executeUpdate();
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}



-- SQL to create the users table
CREATE TABLE IF NOT EXISTS users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(255) NOT NULL UNIQUE,
    password VARCHAR(255) NOT NULL
);