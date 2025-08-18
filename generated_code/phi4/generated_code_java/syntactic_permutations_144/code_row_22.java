import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscribe {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String email = "example@example.com";
        int result = checkAndUnsubscribe(email);
        System.out.println("Result: " + result);
    }

    public static int checkAndUnsubscribe(String email) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // Check if the email exists
            String sqlCheck = "SELECT COUNT(*) FROM users WHERE email = ?";
            pstmt = conn.prepareStatement(sqlCheck);
            pstmt.setString(1, email);
            rs = pstmt.executeQuery();

            if (rs.next() && rs.getInt(1) > 0) {
                // Email exists, call unsubscribe script
                int unsubscribeResult = runUnsubscribeScript(email);

                return unsubscribeResult == 0 ? 1 : 0;
            }

            return 0;

        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        } finally {
            try {
                if (rs != null) rs.close();
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    private static int runUnsubscribeScript(String email) {
        // Simulate running an external script
        // In a real scenario, you would execute the script and capture its exit code
        System.out.println("Running unsubscribe script for: " + email);

        // Mocking script result as 0 (success)
        return 0;
    }
}