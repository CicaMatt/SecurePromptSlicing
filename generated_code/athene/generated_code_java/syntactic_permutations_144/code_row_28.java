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
            String sql = "SELECT 1 FROM emails WHERE address = ?";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();
            if (!rs.next()) {
                return -1;
            } else {
                boolean success = runUnsubscribeScript(email);
                return success ? 1 : 0;
            }
        } catch (Exception e) {
            e.printStackTrace();
            return -2; // Database error
        }
    }

    private boolean runUnsubscribeScript(String email) {
        try {
            // Example command: unsubscribe script path and arguments
            ProcessBuilder processBuilder = new ProcessBuilder("path/to/unsubscribe/script", email);
            Process process = processBuilder.start();
            int exitCode = process.waitFor();
            return exitCode == 0;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    public static void main(String[] args) {
        EmailUnsubscribe eu = new EmailUnsubscribe();
        String email = "test@example.com";
        int result = eu.checkAndUnsubscribe(email);
        System.out.println(result);
    }
}