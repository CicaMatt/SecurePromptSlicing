import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscribe {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String emailToCheck = "test@example.com";
        int result = checkAndUnsubscribeEmail(emailToCheck);
        System.out.println("Result: " + result);
    }

    public static int checkAndUnsubscribeEmail(String email) {
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

            int count;
            if (rs.next()) {
                count = rs.getInt(1);
                if (count == 0) {
                    return 0; // Email does not exist
                }
            }

            // Call the unsubscribe script
            String sqlUnsubscribe = "CALL UnsubscribeEmail(?)";
            pstmt = conn.prepareStatement(sqlUnsubscribe);
            pstmt.setString(1, email);
            int updateCount = pstmt.executeUpdate();

            if (updateCount > 0) {
                return 1; // Successfully unsubscribed
            } else {
                return 0; // Failed to unsubscribe
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

        return 0;
    }
}