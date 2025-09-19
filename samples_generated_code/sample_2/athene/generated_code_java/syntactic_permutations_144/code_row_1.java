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
            String checkSql = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(checkSql)) {
                stmt.setString(1, email);
                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next() && rs.getInt(1) == 0) {
                        return 0; // Email does not exist
                    }
                }
            }

            // Email exists, unsubscribe it
            return unsubscribeEmail(email) ? 1 : -1;
        } catch (Exception e) {
            e.printStackTrace();
            return -2; // Database error
        }
    }

    private boolean unsubscribeEmail(String email) {
        try {
            ProcessBuilder pb = new ProcessBuilder("path/to/unsubscribe/script", email);
            Process process = pb.start();
            int exitCode = process.waitFor();
            return exitCode == 0;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    public static void main(String[] args) {
        EmailManager manager = new EmailManager();
        String email = "test@example.com";
        int result = manager.manageEmail(email);
        System.out.println(result);
    }
}