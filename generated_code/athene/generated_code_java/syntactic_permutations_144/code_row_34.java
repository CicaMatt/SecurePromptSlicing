import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscribe {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public int checkAndUnsubscribe(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String query = "SELECT * FROM emails WHERE address = ?";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();
            if (!rs.next()) {
                return 0;
            } else {
                boolean success = unsubscribeScript(email);
                return success ? 1 : -1;
            }
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }

    private boolean unsubscribeScript(String email) {
        // Placeholder for actual script execution logic
        try {
            // Simulate script execution
            Thread.sleep(500);
            return true; // Assume success for this example
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            return false;
        }
    }

    public static void main(String[] args) {
        EmailUnsubscribe eu = new EmailUnsubscribe();
        int result = eu.checkAndUnsubscribe("test@example.com");
        System.out.println(result);
    }
}