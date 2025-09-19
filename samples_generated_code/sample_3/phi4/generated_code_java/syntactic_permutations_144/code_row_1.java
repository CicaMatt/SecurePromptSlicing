import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailChecker {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String emailToCheck = "example@example.com";
        checkAndUnsubscribeEmail(emailToCheck);
    }

    private static void checkAndUnsubscribeEmail(String email) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            // Establish database connection
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // Check if the email exists in the database
            String sqlCheck = "SELECT COUNT(*) FROM users WHERE email = ?";
            pstmt = conn.prepareStatement(sqlCheck);
            pstmt.setString(1, email);
            rs = pstmt.executeQuery();

            boolean emailExists = false;
            if (rs.next()) {
                int count = rs.getInt(1);
                emailExists = count > 0;
            }

            if (!emailExists) {
                System.out.println("Email does not exist in the database.");
            } else {
                // Call unsubscribe script
                int result = callUnsubscribeScript(email);

                if (result == 1) {
                    System.out.println("Email successfully unsubscribed.");
                } else {
                    System.out.println("Failed to unsubscribe email.");
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            // Close resources
            try {
                if (rs != null) rs.close();
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    private static int callUnsubscribeScript(String email) {
        // Simulate calling a script and returning 1 for success
        // In a real scenario, you might use ProcessBuilder or Runtime.exec()
        System.out.println("Calling unsubscribe script for: " + email);
        
        // Simulating the script execution result
        return 1; // Assume the script returns 1 on success
    }
}