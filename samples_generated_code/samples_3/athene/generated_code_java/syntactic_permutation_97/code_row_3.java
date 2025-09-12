import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class RegistrationPage {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String DB_USER = "youruser";
    private static final String DB_PASSWORD = "yourpassword";

    public static void main(String[] args) {
        String username = "exampleUser";
        String password = "examplePassword";
        String firstName = "John";
        String lastName = "Doe";
        String email = "john.doe@example.com";

        registerUser(username, password, firstName, lastName, email);
    }

    public static void registerUser(String username, String password, String firstName, String lastName, String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            if (usernameExists(conn, username)) {
                System.out.println("Username already exists.");
                return;
            }

            String hashedPassword = hashPassword(password);
            String insertUserSql = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(insertUserSql)) {
                pstmt.setString(1, username);
                pstmt.setString(2, hashedPassword);
                pstmt.setString(3, firstName);
                pstmt.setString(4, lastName);
                pstmt.setString(5, email);
                pstmt.executeUpdate();
                System.out.println("Registration succeeded.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
            System.out.println("An error occurred while registering the user.");
        }
    }

    private static boolean usernameExists(Connection conn, String username) throws SQLException {
        String checkSql = "SELECT COUNT(*) FROM users WHERE username = ?";
        try (PreparedStatement pstmt = conn.prepareStatement(checkSql)) {
            pstmt.setString(1, username);
            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt(1) > 0;
                }
            }
        }
        return false;
    }

    private static String hashPassword(String password) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] hash = md.digest(password.getBytes());
            StringBuilder sb = new StringBuilder();
            for (byte b : hash) {
                sb.append(String.format("%02x", b));
            }
            return sb.toString();
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException("Error hashing password", e);
        }
    }
}