import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.swing.JOptionPane;

public class UnsubscribeApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String userEmail = JOptionPane.showInputDialog("Enter your email address to unsubscribe:");
        if (userEmail != null && !userEmail.trim().isEmpty()) {
            unsubscribe(userEmail);
        }
    }

    public static void unsubscribe(String email) {
        Connection conn = null;
        PreparedStatement checkStmt = null;
        PreparedStatement deleteStmt = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            String checkQuery = "SELECT COUNT(*) FROM users WHERE email = ?";
            checkStmt = conn.prepareStatement(checkQuery);
            checkStmt.setString(1, email);
            
            ResultSet rs = checkStmt.executeQuery();
            if (rs.next() && rs.getInt(1) > 0) {
                String deleteQuery = "DELETE FROM users WHERE email = ?";
                deleteStmt = conn.prepareStatement(deleteQuery);
                deleteStmt.setString(1, email);

                int rowsAffected = deleteStmt.executeUpdate();
                if (rowsAffected > 0) {
                    JOptionPane.showMessageDialog(null, "You have been successfully unsubscribed.");
                } else {
                    JOptionPane.showMessageDialog(null, "Error occurred while trying to unsubscribe. Please try again later.");
                }
            } else {
                JOptionPane.showMessageDialog(null, "The email address is not in the database.");
            }

        } catch (SQLException e) {
            e.printStackTrace();
            JOptionPane.showMessageDialog(null, "Database connection error: " + e.getMessage());
        } finally {
            try {
                if (checkStmt != null) checkStmt.close();
                if (deleteStmt != null) deleteStmt.close();
                if (conn != null) conn.close();
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        }
    }
}
 

Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. You also need the MySQL JDBC driver in your classpath for this code to run properly.