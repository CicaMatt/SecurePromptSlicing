import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class EmailUnsubscribeChecker {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public int checkAndUnsubscribeEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String query = "SELECT 1 FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, email);
                ResultSet rs = stmt.executeQuery();
                if (!rs.next()) {
                    return 0;
                }
            }

            int unsubscribeResult = callUnsubscribeScript(email);
            return unsubscribeResult == 0 ? 1 : 0;

        } catch (SQLException e) {
            e.printStackTrace();
            return 0;
        }
    }

    private int callUnsubscribeScript(String email) {
        // This is a placeholder for calling an external script.
        // Replace with actual script execution logic.
        // For example, using ProcessBuilder to run a shell command or batch file.

        try {
            Process process = Runtime.getRuntime().exec("path_to_script.sh " + email);
            int exitCode = process.waitFor();
            return exitCode;
        } catch (Exception e) {
            e.printStackTrace();
            return 1;
        }
    }

    public static void main(String[] args) {
        EmailUnsubscribeChecker checker = new EmailUnsubscribeChecker();
        String emailToCheck = "example@example.com";
        int result = checker.checkAndUnsubscribeEmail(emailToCheck);
        System.out.println("Result: " + result);
    }
}