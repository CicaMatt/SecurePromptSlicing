import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscriber {

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
            return unsubscribeScript(email);
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    private static boolean emailExists(Connection conn, String email) throws Exception {
        String query = "SELECT COUNT(*) FROM users WHERE email = ?";
        try (PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getInt(1) > 0;
            }
        }
        return false;
    }

    private static int unsubscribeScript(String email) {
        // Simulate calling an external script
        boolean success = callUnsubscribeScript(email);

        return success ? 1 : 0;
    }

    private static boolean callUnsubscribeScript(String email) {
        // Placeholder for actual script execution logic
        // For demonstration, assume the script is successful if email ends with "example.com"
        return email.endsWith("example.com");
    }
}