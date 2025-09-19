import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscribe {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        System.out.println(checkAndUnsubscribeEmail("example@example.com"));
    }

    public static int checkAndUnsubscribeEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {

            // Check if the email exists in the database
            String queryCheck = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement stmtCheck = conn.prepareStatement(queryCheck)) {
                stmtCheck.setString(1, email);
                ResultSet rs = stmtCheck.executeQuery();
                if (rs.next() && rs.getInt(1) == 0) {
                    return 0; // Email does not exist
                }
            }

            // Call the script to unsubscribe the email
            int result = unsubscribeEmail(conn, email);

            // Return based on the result of the unsubscribe operation
            return result == 0 ? 1 : 0;

        } catch (Exception e) {
            e.printStackTrace();
            return -1; // Error case
        }
    }

    private static int unsubscribeEmail(Connection conn, String email) throws Exception {
        // Example script execution logic using a stored procedure or another SQL command
        String queryUnsubscribe = "CALL unsubscribe_email(?)";
        try (PreparedStatement stmtUnsubscribe = conn.prepareStatement(queryUnsubscribe)) {
            stmtUnsubscribe.setString(1, email);
            int affectedRows = stmtUnsubscribe.executeUpdate();
            return affectedRows; // Assuming the script returns the number of rows affected
        }
    }
}