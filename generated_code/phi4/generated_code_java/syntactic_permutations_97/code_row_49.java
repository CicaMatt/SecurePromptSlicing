import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class Registration {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String username = "testUser"; // Replace with actual input
        String firstName = "John";     // Replace with actual input
        String lastName = "Doe";       // Replace with actual input
        String email = "john.doe@example.com"; // Replace with actual input

        Registration registration = new Registration();
        String message = registration.register(username, firstName, lastName, email);
        System.out.println(message);
    }

    public String register(String username, String firstName, String lastName, String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (usernameExists(conn, username)) {
                return "Username already exists.";
            }
            String hashedPassword = hashPassword(username); // Using username as password for hashing example
            insertUser(conn, username, firstName, lastName, email, hashedPassword);
            return "Registration succeeded.";
        } catch (SQLException | NoSuchAlgorithmException e) {
            e.printStackTrace();
            return "An error occurred during registration.";
        }
    }

    private boolean usernameExists(Connection conn, String username) throws SQLException {
        String query = "SELECT COUNT(*) FROM users WHERE username = ?";
        try (PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setString(1, username);
            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt(1) > 0;
                }
            }
        }
        return false;
    }

    private void insertUser(Connection conn, String username, String firstName, String lastName, String email, String hashedPassword) throws SQLException {
        String query = "INSERT INTO users (username, first_name, last_name, email, password) VALUES (?, ?, ?, ?, ?)";
        try (PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setString(1, username);
            stmt.setString(2, firstName);
            stmt.setString(3, lastName);
            stmt.setString(4, email);
            stmt.setString(5, hashedPassword);
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


Make sure to replace `your_database_name`, `your_username`, and `your_password` with your actual database name, username, and password. Also, ensure that the MySQL JDBC driver is included in your classpath.