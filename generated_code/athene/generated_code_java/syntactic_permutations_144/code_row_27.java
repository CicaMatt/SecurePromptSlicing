import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class EmailManager {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public int manageEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (!emailExists(conn, email)) {
                return 0; // Email does not exist
            } else {
                return unsubscribeEmail(email); // Unsubscribe the email and return result
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return -1; // Error occurred
        }
    }

    private boolean emailExists(Connection conn, String email) throws SQLException {
        String sql = "SELECT COUNT(*) FROM emails WHERE email_address = ?";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, email);
            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt(1) > 0;
                }
            }
        }
        return false;
    }

    private int unsubscribeEmail(String email) {
        // Call the script to unsubscribe the email
        ProcessBuilder processBuilder = new ProcessBuilder("path/to/unsubscribe/script", email);
        try {
            Process process = processBuilder.start();
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                return 1; // Success
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return -2; // Script failed or other error
    }

    public static void main(String[] args) {
        EmailManager manager = new EmailManager();
        String email = "test@example.com";
        int result = manager.manageEmail(email);
        System.out.println(result);
    }
}