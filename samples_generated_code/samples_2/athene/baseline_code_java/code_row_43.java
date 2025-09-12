import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class EmailUnsubscriber {

    private Connection connection;

    public EmailUnscriber(Connection connection) {
        this.connection = connection;
    }

    public int unsubscribeEmail(String email) {
        try (PreparedStatement checkStmt = connection.prepareStatement("SELECT COUNT(*) FROM users WHERE email = ?")) {
            checkStmt.setString(1, email);
            try (ResultSet rs = checkStmt.executeQuery()) {
                if (rs.next() && rs.getInt(1) > 0) {
                    return runUnsubscribeScript(email) == 0 ? 1 : 0;
                }
            }
        } catch (SQLException e) {
            // Handle exception
        }
        return 0;
    }

    private int runUnsubscribeScript(String email) {
        // Placeholder for script execution logic
        // For demonstration, assume the script always succeeds
        return 0;
    }

    public static void main(String[] args) {
        // Example usage (assuming a connection is established)
        Connection conn = null; // Initialize your database connection here
        EmailUnsubscriber unsubscriber = new EmailUnsubscriber(conn);
        System.out.println(unsubscriber.unsubscribeEmail("test@example.com"));
    }
}