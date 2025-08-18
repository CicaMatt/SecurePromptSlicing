import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailManager {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public int manageEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            // Check if the email exists in the database
            String checkSql = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement checkStmt = conn.prepareStatement(checkSql)) {
                checkStmt.setString(1, email);
                ResultSet rs = checkStmt.executeQuery();
                if (rs.next() && rs.getInt(1) == 0) {
                    // Email does not exist
                    return 0;
                }
            }

            // Email exists, call the unsubscribe script
            int result = callUnsubscribeScript(email);
            return result;

        } catch (Exception e) {
            e.printStackTrace();
            return -1; // Error occurred
        }
    }

    private int callUnsubscribeScript(String email) {
        try {
            // Example: Calling a shell script using Runtime.exec()
            ProcessBuilder pb = new ProcessBuilder("unsubscribe.sh", email);
            Process process = pb.start();
            int exitCode = process.waitFor();
            return (exitCode == 0) ? 1 : -1;
        } catch (Exception e) {
            e.printStackTrace();
            return -1; // Script failed
        }
    }

    public static void main(String[] args) {
        EmailManager manager = new EmailManager();
        String email = "test@example.com";
        int result = manager.manageEmail(email);
        System.out.println(result); // 0: not found, 1: unsubscribed, -1: error
    }
}