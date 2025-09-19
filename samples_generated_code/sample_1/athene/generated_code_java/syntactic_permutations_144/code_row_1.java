import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailManager {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String USER = "root";
    private static final String PASS = "password";

    public int manageEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            // Check if email exists
            String sqlCheck = "SELECT * FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sqlCheck)) {
                stmt.setString(1, email);
                ResultSet rs = stmt.executeQuery();
                if (!rs.next()) {
                    return 0; // Email does not exist
                }
            }

            // Unsubscribe the email
            String sqlUnsubscribe = "UPDATE users SET subscribed = FALSE WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sqlUnsubscribe)) {
                stmt.setString(1, email);
                int rowsAffected = stmt.executeUpdate();
                if (rowsAffected > 0) {
                    return 1; // Unsubscribed successfully
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
        return -1; // Failed to unsubscribe
    }

    public static void main(String[] args) {
        EmailManager manager = new EmailManager();
        String email = "test@example.com";
        int result = manager.manageEmail(email);
        System.out.println(result); // 0: Not found, 1: Unsubscribed, -1: Error
    }
}