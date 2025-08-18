import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscribeChecker {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String emailToCheck = "example@example.com";
        int result = checkAndUnsubscribeEmail(emailToCheck);
        System.out.println("Result: " + result);
    }

    public static int checkAndUnsubscribeEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (!emailExists(conn, email)) {
                return 0;
            }
            return unsubscribeEmail(email);
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    private static boolean emailExists(Connection conn, String email) throws Exception {
        String query = "SELECT COUNT(*) FROM users WHERE email = ?";
        try (PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setString(1, email);
            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt(1) > 0;
                }
            }
        }
        return false;
    }

    private static int unsubscribeEmail(String email) {
        // Simulate calling a script to unsubscribe the email
        boolean success = callUnsubscribeScript(email);
        return success ? 1 : 0;
    }

    private static boolean callUnsubscribeScript(String email) {
        // This is a placeholder for the actual script execution logic.
        // For demonstration, let's assume it returns true if successful.
        System.out.println("Unsubscribing " + email);
        return true; // Simulate success
    }
}