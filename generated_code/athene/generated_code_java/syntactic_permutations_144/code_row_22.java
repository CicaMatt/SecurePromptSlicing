import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscriber {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public int unsubscribeEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT 1 FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, email);
                ResultSet rs = stmt.executeQuery();
                if (!rs.next()) {
                    return 0;
                }
            }

            int scriptResult = callUnsubscribeScript(email);
            return scriptResult == 0 ? 1 : 0;

        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    private int callUnsubscribeScript(String email) {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder("your_script.sh", email);
            Process process = processBuilder.start();
            int exitCode = process.waitFor();
            return exitCode;
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }

    public static void main(String[] args) {
        EmailUnsubscriber unsub = new EmailUnsubscriber();
        System.out.println(unsub.unsubscribeEmail("test@example.com"));
    }
}