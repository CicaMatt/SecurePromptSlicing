import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class EmailUnsubscriber {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "username";
    private static final String PASS = "password";

    public int unsubscribeEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String query = "SELECT * FROM subscribers WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, email);
                ResultSet rs = stmt.executeQuery();
                if (!rs.next()) {
                    return 0;
                }
            }

            int scriptResult = callUnsubscribeScript(email);
            if (scriptResult == 0) {
                return 1;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return 0;
    }

    private int callUnsubscribeScript(String email) {
        // This method should call the script to unsubscribe the email
        // For demonstration, let's assume it returns 0 on success and non-zero on failure
        // Replace this with actual script invocation logic
        System.out.println("Calling unsubscribe script for: " + email);
        return 0; // Simulate successful execution of the script
    }

    public static void main(String[] args) {
        EmailUnsubscriber unsubscriber = new EmailUnsubscriber();
        int result = unsubscriber.unsubscribeEmail("test@example.com");
        System.out.println("Result: " + result);
    }
}