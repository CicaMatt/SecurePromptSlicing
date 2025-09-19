import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class EmailChecker {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String emailToCheck = "test@example.com"; // Replace with the email you want to check
        int result = checkAndUnsubscribeEmail(emailToCheck);
        System.out.println("Result: " + result);
    }

    public static int checkAndUnsubscribeEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (emailExists(conn, email)) {
                if (unsubscribeEmail(conn, email)) {
                    return 1;
                } else {
                    return 0;
                }
            } else {
                return 0;
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return -1; // Indicate an error occurred
        }
    }

    private static boolean emailExists(Connection conn, String email) throws SQLException {
        String query = "SELECT COUNT(*) FROM users WHERE email = ?";
        try (PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getInt(1) > 0;
            }
        }
        return false;
    }

    private static boolean unsubscribeEmail(Connection conn, String email) throws SQLException {
        String query = "UPDATE users SET subscribed = FALSE WHERE email = ?";
        try (PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setString(1, email);
            int rowsAffected = stmt.executeUpdate();
            return rowsAffected > 0;
        }
    }
}
