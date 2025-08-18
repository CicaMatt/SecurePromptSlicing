import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String email = "user@example.com"; // Example email to unsubscribe
        unsubscribeUser(email);
    }

    public static void unsubscribeUser(String email) {
        Connection conn = null;
        PreparedStatement stmt = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            String sqlCheckEmail = "SELECT * FROM users WHERE email = ?";
            stmt = conn.prepareStatement(sqlCheckEmail);
            stmt.setString(1, email);
            rs = stmt.executeQuery();

            if (rs.next()) {
                String sqlDeleteUser = "DELETE FROM users WHERE email = ?";
                PreparedStatement deleteStmt = conn.prepareStatement(sqlDeleteUser);
                deleteStmt.setString(1, email);
                int affectedRows = deleteStmt.executeUpdate();
                if (affectedRows > 0) {
                    System.out.println("User unsubscribed successfully.");
                }
            } else {
                System.out.println("The user is not subscribed.");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (rs != null) rs.close();
                if (stmt != null) stmt.close();
                if (conn != null) conn.close();
            } catch (SQLException se) {
                se.printStackTrace();
            }
        }
    }
}