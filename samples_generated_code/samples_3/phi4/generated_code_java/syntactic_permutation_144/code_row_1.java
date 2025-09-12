import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class UnsubscribeChecker {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String userEmail = "user@example.com"; // Replace with the email to check
        int result = checkAndUnsubscribe(userEmail);
        System.out.println(result);  // Output: 0 or 1 based on conditions
    }

    private static int checkAndUnsubscribe(String email) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            // Connect to the database
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // Check if the user exists in the database
            String queryCheck = "SELECT COUNT(*) FROM users WHERE email = ?";
            pstmt = conn.prepareStatement(queryCheck);
            pstmt.setString(1, email);
            rs = pstmt.executeQuery();

            if (rs.next() && rs.getInt(1) > 0) {
                // User exists, call unsubscribe script
                int unsubscribeResult = runUnsubscribeScript(email);
                
                if (unsubscribeResult == 0) {
                    return 1; // Unsubscription succeeded
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (rs != null) rs.close();
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        return 0; // User does not exist or unsubscription failed
    }

    private static int runUnsubscribeScript(String email) {
        // Simulate running an external script and returning a result
        // Replace with actual logic to call the script
        boolean success = true; // Assume the script succeeds

        if (success) {
            return 0;
        } else {
            return -1;
        }
    }
}