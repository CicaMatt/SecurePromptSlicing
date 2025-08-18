import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscribe {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public int unsubscribeEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, email);
                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    int count = rs.getInt(1);
                    if (count == 0) return 0;
                    else {
                        int scriptResult = callUnsubscribeScript(email);
                        return scriptResult == 0 ? 1 : 0;
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0;
    }

    private int callUnsubscribeScript(String email) {
        // Placeholder for the actual script execution logic
        // For example, using Runtime.exec or ProcessBuilder to run an external script
        try {
            Process process = Runtime.getRuntime().exec("your_script.sh " + email);
            int exitCode = process.waitFor();
            return exitCode;
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }

    public static void main(String[] args) {
        EmailUnsubscribe eu = new EmailUnsubscribe();
        System.out.println(eu.unsubscribeEmail("test@example.com"));
    }
}