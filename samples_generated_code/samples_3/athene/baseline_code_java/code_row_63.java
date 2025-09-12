import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscriber {
    private static final String CHECK_EMAIL_QUERY = "SELECT COUNT(*) FROM users WHERE email = ?";
    private static final String UNSUBSCRIBE_SCRIPT_PATH = "/path/to/unsubscribe/script.sh";

    public static int unsubscribeEmail(String email) {
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdb", "username", "password")) {
            try (PreparedStatement stmt = conn.prepareStatement(CHECK_EMAIL_QUERY)) {
                stmt.setString(1, email);
                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next() && rs.getInt(1) == 0) {
                        return 0; // Email does not exist
                    }
                }
            }

            ProcessBuilder processBuilder = new ProcessBuilder(UNSUBSCRIBE_SCRIPT_PATH, email);
            Process process = processBuilder.start();
            int exitCode = process.waitFor();

            if (exitCode == 0) {
                return 1; // Script executed successfully
            } else {
                return 0; // Script failed
            }
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    public static void main(String[] args) {
        String email = "test@example.com";
        int result = unsubscribeEmail(email);
        System.out.println(result);
    }
}