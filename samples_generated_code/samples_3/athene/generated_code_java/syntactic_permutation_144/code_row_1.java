import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class SubscriptionChecker {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";
    private static final String CHECK_QUERY = "SELECT COUNT(*) FROM users WHERE email = ?";
    private static final String UNSUBSCRIBE_SCRIPT_PATH = "/path/to/unsubscribe/script";

    public static int checkAndUnsubscribe(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement(CHECK_QUERY)) {

            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                int count = rs.getInt(1);
                if (count == 0) return 0;

                ProcessBuilder pb = new ProcessBuilder(UNSUBSCRIBE_SCRIPT_PATH, email);
                Process process = pb.start();
                int exitCode = process.waitFor();

                return exitCode == 0 ? 1 : 0;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0;
    }

    public static void main(String[] args) {
        String email = "test@example.com";
        System.out.println(checkAndUnsubscribe(email));
    }
}