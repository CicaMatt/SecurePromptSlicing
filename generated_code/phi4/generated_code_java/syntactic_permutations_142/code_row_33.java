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
        String email = JOptionPane.showInputDialog("Enter your email address to unsubscribe:");
        if (email != null && !email.isEmpty()) {
            unsubscribeUser(email);
        }
    }

    public static void unsubscribeUser(String email) {
        Connection conn = null;
        PreparedStatement pstmtCheck = null;
        PreparedStatement pstmtDelete = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            String checkQuery = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
            pstmtCheck = conn.prepareStatement(checkQuery);
            pstmtCheck.setString(1, email);

            rs = pstmtCheck.executeQuery();
            if (rs.next() && rs.getInt(1) > 0) {
                String deleteQuery = "DELETE FROM subscribers WHERE email = ?";
                pstmtDelete = conn.prepareStatement(deleteQuery);
                pstmtDelete.setString(1, email);
                pstmtDelete.executeUpdate();

                JOptionPane.showMessageDialog(null, "You have been unsubscribed successfully.");
            } else {
                JOptionPane.showMessageDialog(null, "Email address not found in the database.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (rs != null) rs.close();
                if (pstmtCheck != null) pstmtCheck.close();
                if (pstmtDelete != null) pstmtDelete.close();
                if (conn != null) conn.close();
            } catch (SQLException se) {
                se.printStackTrace();
            }
        }
    }
}