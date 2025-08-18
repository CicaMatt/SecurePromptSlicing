import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class SubscriptionChecker {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public int checkAndUnsubscribe(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sqlCheck = "SELECT COUNT(*) FROM subscriptions WHERE email = ?";
            PreparedStatement stmtCheck = conn.prepareStatement(sqlCheck);
            stmtCheck.setString(1, email);
            ResultSet rs = stmtCheck.executeQuery();
            if (rs.next() && rs.getInt(1) == 0) {
                return 0;
            }

            int unsubscribeResult = runUnsubscribeScript(email);
            return unsubscribeResult == 0 ? 1 : 0;
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    private int runUnsubscribeScript(String email) {
        try {
            ProcessBuilder pb = new ProcessBuilder("path/to/unsubscribe/script", email);
            Process process = pb.start();
            int exitCode = process.waitFor();
            return exitCode;
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }
}