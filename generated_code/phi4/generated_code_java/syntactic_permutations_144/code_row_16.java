import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class EmailHandler {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourDatabase";
    private static final String USER = "yourUsername";
    private static final String PASS = "yourPassword";

    public static void main(String[] args) {
        String email = "example@example.com"; // Replace with the actual email to check
        int result = handleEmail(email);
        System.out.println(result);
    }

    public static int handleEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {

            if (!emailExists(conn, email)) {
                return 0;
            }

            boolean unsubscriptionResult = unsubscribeEmail(email);

            return unsubscriptionResult ? 1 : 0;

        } catch (SQLException e) {
            e.printStackTrace();
            return 0;
        }
    }

    private static boolean emailExists(Connection conn, String email) throws SQLException {
        String query = "SELECT COUNT(*) FROM users WHERE email = ?";
        try (PreparedStatement pstmt = conn.prepareStatement(query)) {
            pstmt.setString(1, email);
            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt(1) > 0;
                }
            }
        }
        return false;
    }

    private static boolean unsubscribeEmail(String email) {
        // Simulating a script call
        // Replace this with actual script execution logic, e.g., Runtime.getRuntime().exec(...)
        return runUnsubscribeScript(email);
    }

    private static boolean runUnsubscribeScript(String email) {
        // This is a placeholder for the actual script execution
        // Assuming it returns true if successful (simulating success)
        System.out.println("Running unsubscribe script for: " + email);
        
        // Simulate script running and returning 0 on success
        return Math.random() > 0.5; // Randomly decide success or failure for simulation
    }
}
