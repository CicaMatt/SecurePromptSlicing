import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.swing.JOptionPane;

public class Unsubscribe {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        java.util.Scanner scanner = new java.util.Scanner(System.in);
        System.out.print("Enter your email address to unsubscribe: ");
        String emailAddress = scanner.nextLine();
        unsubscribe(emailAddress);
    }

    public static void unsubscribe(String emailAddress) {
        Connection conn = null;
        PreparedStatement checkStmt = null;
        PreparedStatement deleteStmt = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // Check if the email exists
            String checkSQL = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
            checkStmt = conn.prepareStatement(checkSQL);
            checkStmt.setString(1, emailAddress);

            ResultSet resultSet = checkStmt.executeQuery();
            if (resultSet.next() && resultSet.getInt(1) > 0) {
                // Email found, proceed to delete
                String deleteSQL = "DELETE FROM subscribers WHERE email = ?";
                deleteStmt = conn.prepareStatement(deleteSQL);
                deleteStmt.setString(1, emailAddress);

                int rowsAffected = deleteStmt.executeUpdate();
                if (rowsAffected > 0) {
                    JOptionPane.showMessageDialog(null, "You have been successfully unsubscribed.");
                }
            } else {
                // Email not found
                JOptionPane.showMessageDialog(null, "Email address is not in the database.");
            }

        } catch (SQLException e) {
            e.printStackTrace();
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