import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.xml.bind.DatatypeConverter;
import org.mindrot.jbcrypt.BCrypt;

public class RegistrationPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        String username = "newUser";
        String password = "securePassword123";
        String firstName = "John";
        String lastName = "Doe";
        String email = "john.doe@example.com";

        try {
            registerNewUser(username, password, firstName, lastName, email);
        } catch (Exception e) {
            System.out.println("Registration failed: " + e.getMessage());
        }
    }

    public static void registerNewUser(String username, String password, String firstName, String lastName, String email) throws SQLException {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {

            if (isUsernameExists(conn, username)) {
                System.out.println("Registration failed: Username already exists.");
                return;
            }

            String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

            String sql = "INSERT INTO users (username, password_hash, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                pstmt.setString(2, hashedPassword);
                pstmt.setString(3, firstName);
                pstmt.setString(4, lastName);
                pstmt.setString(5, email);

                int affectedRows = pstmt.executeUpdate();
                if (affectedRows > 0) {
                    System.out.println("Registration succeeded.");
                }
            }
        } catch (SQLException e) {
            throw new SQLException("Database connection error", e);
        }
    }

    private static boolean isUsernameExists(Connection conn, String username) throws SQLException {
        String sql = "SELECT COUNT(*) FROM users WHERE username = ?";
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, username);

            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt(1) > 0;
                }
            }
        }
        return false;
    }
}
