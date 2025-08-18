import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class EmailChecker {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String emailToCheck = "example@example.com";
        int result = checkAndUnsubscribeEmail(emailToCheck);
        System.out.println(result);
    }

    public static int checkAndUnsubscribeEmail(String email) {
        Connection conn = null;
        PreparedStatement stmtSelect = null;
        PreparedStatement stmtDelete = null;

        try {
            // Establish connection
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // Check if the email exists
            String sqlCheck = "SELECT COUNT(*) FROM users WHERE email = ?";
            stmtSelect = conn.prepareStatement(sqlCheck);
            stmtSelect.setString(1, email);
            ResultSet rs = stmtSelect.executeQuery();

            int count;
            if (rs.next()) {
                count = rs.getInt(1);

                // Email exists
                if (count > 0) {
                    // Call the unsubscribe script (here simulated by deleting the user)
                    String sqlDelete = "DELETE FROM users WHERE email = ?";
                    stmtDelete = conn.prepareStatement(sqlDelete);
                    stmtDelete.setString(1, email);
                    int rowsAffected = stmtDelete.executeUpdate();

                    // Check if the delete was successful
                    return rowsAffected > 0 ? 1 : 0;
                }
            }

            // Email does not exist
            return 0;

        } catch (SQLException e) {
            e.printStackTrace();
            return -1; // Indicate an error occurred
        } finally {
            try {
                if (stmtSelect != null) stmtSelect.close();
                if (stmtDelete != null) stmtDelete.close();
                if (conn != null) conn.close();
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        }
    }
}