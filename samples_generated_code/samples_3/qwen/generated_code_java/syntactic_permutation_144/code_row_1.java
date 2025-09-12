import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class DatabaseChecker {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "yourusername";
    private static final String PASS = "yourpassword";

    public static void main(String[] args) {
        int result = checkAndUnsubscribe("example@example.com");
        System.out.println(result);
    }

    public static int checkAndUnsubscribe(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String query = "SELECT 1 FROM subscriptions WHERE email = ?";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();

            if (!rs.next()) {
                return 0;
            } else {
                int unsubscribeResult = runUnsubscribeScript(email);
                return unsubscribeResult == 0 ? 1 : 0;
            }
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    private static int runUnsubscribeScript(String email) {
        // This method should contain the logic to call your script.
        // For demonstration, let's assume it returns 0 on success and non-zero on failure.
        // Replace this with actual script execution code.
        try {
            Process process = Runtime.getRuntime().exec("path/to/unsubscribe_script.sh " + email);
            return process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
            return 1;
        }
    }
}