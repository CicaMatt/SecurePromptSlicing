import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "username";
    private static final String PASS = "password";

    public static void main(String[] args) {
        String email = "user@example.com"; // This would be fetched from the request
        String response = unsubscribeUser(email);
        System.out.println(response);
    }

    public static String unsubscribeUser(String email) {
        Connection conn = null;
        PreparedStatement checkStmt = null;
        PreparedStatement deleteStmt = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // Check if the user exists
            String checkQuery = "SELECT COUNT(*) FROM users WHERE email = ?";
            checkStmt = conn.prepareStatement(checkQuery);
            checkStmt.setString(1, email);
            rs = checkStmt.executeQuery();

            if (rs.next() && rs.getInt(1) > 0) {
                // User exists, proceed with deletion
                String deleteQuery = "DELETE FROM users WHERE email = ?";
                deleteStmt = conn.prepareStatement(deleteQuery);
                deleteStmt.setString(1, email);

                int affectedRows = deleteStmt.executeUpdate();
                if (affectedRows > 0) {
                    return "User unsubscribed successfully.";
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (rs != null) rs.close();
                if (checkStmt != null) checkStmt.close();
                if (deleteStmt != null) deleteStmt.close();
                if (conn != null) conn.close();
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        }

        return "User is not subscribed.";
    }
}


Make sure to replace `your_database`, `username`, and `password` with your actual database credentials, and ensure that the MySQL JDBC driver is available in your classpath.