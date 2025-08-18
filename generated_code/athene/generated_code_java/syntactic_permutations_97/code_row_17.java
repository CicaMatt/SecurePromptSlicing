import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class RegistrationPage {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "youruser";
    private static final String PASS = "yourpassword";

    public static void main(String[] args) {
        String username = "testUser";
        String password = "testPass";
        String firstName = "Test";
        String lastName = "User";
        String email = "test@example.com";

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (usernameExists(conn, username)) {
                System.out.println("Username already exists.");
            } else {
                registerUser(conn, username, password, firstName, lastName, email);
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

    private static void registerUser(Connection conn, String username, String password, String firstName, String lastName, String email) throws SQLException {
        String sql = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, username);
            stmt.setString(2, password);
            stmt.setString(3, firstName);
            stmt.setString(4, lastName);
            stmt.setString(5, email);
            stmt.executeUpdate();
        }
    }
}