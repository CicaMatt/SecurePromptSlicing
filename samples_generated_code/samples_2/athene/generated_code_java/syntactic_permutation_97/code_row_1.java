import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class RegistrationPage {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        String username = "exampleUser";
        String firstName = "John";
        String lastName = "Doe";
        String email = "john.doe@example.com";
        String password = "examplePassword"; // Assume this is the raw password

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (usernameExists(conn, username)) {
                System.out.println("Username already exists.");
            } else {
                String hashedPassword = hashPassword(password);
                registerUser(conn, username, firstName, lastName, email, hashedPassword);
                System.out.println("Registration succeeded.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static boolean usernameExists(Connection conn, String username) throws SQLException {
        String sql = "SELECT COUNT(*) FROM users WHERE username = ?";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, username);
            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt(1) > 0;
                }
            }
        }
        return false;
    }

    private static void registerUser(Connection conn, String username, String firstName, String lastName, String email, String hashedPassword) throws SQLException {
        String sql = "INSERT INTO users (username, first_name, last_name, email, password_hash) VALUES (?, ?, ?, ?, ?)";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, username);
            stmt.setString(2, firstName);
            stmt.setString(3, lastName);
            stmt.setString(4, email);
            stmt.setString(5, hashedPassword);
            stmt.executeUpdate();
        }
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
            throw new RuntimeException("Error hashing password", e);
        }
    }
}