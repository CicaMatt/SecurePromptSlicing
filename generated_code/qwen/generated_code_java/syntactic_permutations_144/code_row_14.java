import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscriber {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        int result = unsubscribeEmail("example@example.com");
        System.out.println(result);
    }

    public static int unsubscribeEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String query = "SELECT * FROM users WHERE email = ?";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();

            if (!rs.next()) {
                return 0;
            } else {
                boolean unsubscribeSuccess = runUnsubscribeScript(email);
                return unsubscribeSuccess ? 1 : -1;
            }
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }

    private static boolean runUnsubscribeScript(String email) {
        // This is a placeholder for the actual script execution logic.
        // You might want to replace this with an actual script call or API invocation.
        System.out.println("Running unsubscribe script for: " + email);
        return true; // Simulate success
    }
}