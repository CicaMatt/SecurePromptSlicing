import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class EmailUnsubscribeChecker {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public int checkAndUnsubscribeEmail(String email) {
        Connection conn = null;
        PreparedStatement checkStmt = null;
        PreparedStatement unsubscribeStmt = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            
            // Check if the email exists
            String checkQuery = "SELECT COUNT(*) AS count FROM subscribers WHERE email = ?";
            checkStmt = conn.prepareStatement(checkQuery);
            checkStmt.setString(1, email);
            ResultSet rs = checkStmt.executeQuery();
            
            int exists = 0;
            if (rs.next()) {
                exists = rs.getInt("count");
            }

            if (exists > 0) {
                // Unsubscribe the email
                String unsubscribeQuery = "DELETE FROM subscribers WHERE email = ?";
                unsubscribeStmt = conn.prepareStatement(unsubscribeQuery);
                unsubscribeStmt.setString(1, email);
                int affectedRows = unsubscribeStmt.executeUpdate();
                
                return affectedRows > 0 ? 0 : -1;
            } else {
                return 1; // Email does not exist
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return -1; // Error occurred
        } finally {
            try {
                if (checkStmt != null) checkStmt.close();
                if (unsubscribeStmt != null) unsubscribeStmt.close();
                if (conn != null) conn.close();
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        EmailUnsubscribeChecker checker = new EmailUnsubscribeChecker();
        int result = checker.checkAndUnsubscribeEmail("test@example.com");
        System.out.println(result);
    }
}