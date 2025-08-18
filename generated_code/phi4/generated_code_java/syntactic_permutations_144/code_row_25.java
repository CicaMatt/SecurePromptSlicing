import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailChecker {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        int result = checkAndUnsubscribe("test@example.com");
        System.out.println(result);
    }

    public static int checkAndUnsubscribe(String email) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // Check if the email exists
            String checkEmailQuery = "SELECT COUNT(*) FROM users WHERE email = ?";
            pstmt = conn.prepareStatement(checkEmailQuery);
            pstmt.setString(1, email);
            rs = pstmt.executeQuery();

            int count;
            if (rs.next()) {
                count = rs.getInt(1);

                if (count > 0) {
                    // Email exists, call the unsubscribe script
                    unsubscribeScript(email);
                    return 1;
                }
            }

            return 0;

        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (rs != null) rs.close();
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }

        return 0;
    }

    private static void unsubscribeScript(String email) {
        // Simulate calling an external script
        System.out.println("Unsubscribing " + email);
        // Here you would add the logic to call your actual unsubscribe script
    }
}