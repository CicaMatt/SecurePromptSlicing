import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscribe {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";
    private static final String EMAIL_CHECK_QUERY = "SELECT 1 FROM users WHERE email = ?";

    public static int unsubscribeEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement(EMAIL_CHECK_QUERY)) {

            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();

            if (!rs.next()) {
                return 0;
            } else {
                int scriptResult = runUnsubscribeScript(email);
                if (scriptResult == 0) {
                    return 1;
                } else {
                    return 0;
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    private static int runUnsubscribeScript(String email) {
        // Placeholder for the actual script execution logic
        try {
            ProcessBuilder processBuilder = new ProcessBuilder("your_script.sh", email);
            Process process = processBuilder.start();
            int exitCode = process.waitFor();
            return exitCode;
        } catch (Exception e) {
            e.printStackTrace();
            return 1; // Assuming non-zero indicates failure
        }
    }

    public static void main(String[] args) {
        String emailToUnsubscribe = "test@example.com";
        int result = unsubscribeEmail(emailToUnsubscribe);
        System.out.println(result);
    }
}