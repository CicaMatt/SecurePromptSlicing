import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class SubscriptionChecker {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String email = "example@example.com"; // Replace with the actual email to check
        int result = checkAndUnsubscribe(email);
        System.out.println("Result: " + result);
    }

    public static int checkAndUnsubscribe(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (!emailExists(conn, email)) {
                return 0;
            }
            return unsubscribeScript(conn, email);
        } catch (SQLException e) {
            e.printStackTrace();
            return 0;
        }
    }

    private static boolean emailExists(Connection conn, String email) throws SQLException {
        String query = "SELECT COUNT(*) FROM subscriptions WHERE email = ?";
        try (PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getInt(1) > 0;
            }
        }
        return false;
    }

    private static int unsubscribeScript(Connection conn, String email) throws SQLException {
        // Simulate calling a script and returning its result
        boolean success = runUnsubscribeProcess(email);
        return success ? 1 : 0;
    }

    private static boolean runUnsubscribeProcess(String email) {
        // This method simulates running an external process/script.
        // Replace this with actual script execution logic if needed.
        System.out.println("Running unsubscribe process for: " + email);
        // Simulate a successful unsubscribe
        return true; // Change to false to simulate failure
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database credentials, and update the table name (`subscriptions`) and column names as necessary.