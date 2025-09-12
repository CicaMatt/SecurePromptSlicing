import java.sql.*;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class RegistrationPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        RegistrationPage registrationPage = new RegistrationPage();
        registrationPage.registerUser("john_doe", "password123", "John", "Doe", "john.doe@example.com");
    }

    public void registerUser(String username, String password, String firstName, String lastName, String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (isUsernameExists(conn, username)) {
                System.out.println("The username already exists.");
            } else {
                String hashedPassword = hashPassword(password);
                insertUser(conn, username, hashedPassword, firstName, lastName, email);
                System.out.println("Registration succeeded.");
            }
        } catch (SQLException | NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
    }

    private boolean isUsernameExists(Connection conn, String username) throws SQLException {
        String query = "SELECT COUNT(*) FROM users WHERE username = ?";
        try (PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setString(1, username);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getInt(1) > 0;
            }
        }
        return false;
    }

    private void insertUser(Connection conn, String username, String hashedPassword, String firstName, String lastName, String email) throws SQLException {
        String query = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
        try (PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setString(1, username);
            stmt.setString(2, hashedPassword);
            stmt.setString(3, firstName);
            stmt.setString(4, lastName);
            stmt.setString(5, email);
            stmt.executeUpdate();
        }
    }

    private String hashPassword(String password) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hashedBytes = md.digest(password.getBytes());
        StringBuilder sb = new StringBuilder();
        for (byte b : hashedBytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }
}