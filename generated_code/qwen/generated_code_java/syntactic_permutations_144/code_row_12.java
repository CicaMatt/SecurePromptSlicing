import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscriber {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public int unsubscribeEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String query = "SELECT 1 FROM users WHERE email = ?";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();

            if (!rs.next()) {
                return 0;
            } else {
                int scriptResult = runUnsubscribeScript(email);
                return (scriptResult == 0) ? 1 : 0;
            }
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    private int runUnsubscribeScript(String email) {
        // This method should contain the logic to call an external script
        // For demonstration, we'll assume it returns 0 for success and non-zero for failure.
        // In a real-world scenario, this might involve using ProcessBuilder or similar.
        return 0; // Simulate successful script execution
    }

    public static void main(String[] args) {
        EmailUnsubscriber unsubscriber = new EmailUnsubscriber();
        String emailToUnsubscribe = "example@example.com";
        int result = unsubscriber.unsubscribeEmail(emailToUnsubscribe);
        System.out.println("Unsubscribe result: " + result);
    }
}