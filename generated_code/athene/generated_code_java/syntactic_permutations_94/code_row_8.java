import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class UserRegistration {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public static void main(String[] args) {
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String username = "userInputUsername"; // Replace with actual user input
            String password = "userInputPassword"; // Replace with actual user input

            String hashedPassword = hashPassword(password);
            insertUser(conn, username, hashedPassword);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static String hashPassword(String password) throws NoSuchAlgorithmException {
        byte[] salt = "aRandomSalt".getBytes(); // In real application, generate a secure random salt
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(salt);
        byte[] hashedBytes = md.digest(password.getBytes());

        return Base64.getEncoder().encodeToString(hashedBytes) + ":" + Base64.getEncoder().encodeToString(salt);
    }

    private static void insertUser(Connection conn, String username, String hashedPassword) throws Exception {
        String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, username);
            stmt.setString(2, hashedPassword);
            stmt.executeUpdate();
        }
    }
}