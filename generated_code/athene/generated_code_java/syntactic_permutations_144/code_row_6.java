import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class SubscriptionManager {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String USER = "user";
    private static final String PASS = "password";

    public int manageSubscription(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String query = "SELECT COUNT(*) FROM subscriptions WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, email);
                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    int count = rs.getInt(1);
                    if (count == 0) return 0; // Not in database
                }
            }

            // Assuming the script returns an integer value through a method call.
            int scriptResult = callUnsubscribeScript(email);

            return scriptResult == 0 ? 1 : 0;
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    private int callUnsubscribeScript(String email) {
        // Placeholder for actual script execution logic
        return 0; // Simulate successful unsubscribe
    }
}