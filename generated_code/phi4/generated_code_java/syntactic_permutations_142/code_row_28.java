import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.swing.JOptionPane;

public class UnsubscribeApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourDatabaseName";
    private static final String USER = "yourUsername";
    private static final String PASS = "yourPassword";

    public static void main(String[] args) {
        try (java.util.Scanner scanner = new java.util.Scanner(System.in)) {
            System.out.print("Enter your email address to unsubscribe: ");
            String emailAddress = scanner.nextLine();
            unsubscribe(emailAddress);
        }
    }

    public static void unsubscribe(String emailAddress) {
        Connection conn = null;
        PreparedStatement pstmtSelect = null;
        PreparedStatement pstmtDelete = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // Check if email exists
            String sqlCheck = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
            pstmtSelect = conn.prepareStatement(sqlCheck);
            pstmtSelect.setString(1, emailAddress);
            ResultSet rs = pstmtSelect.executeQuery();

            int count = 0;
            if (rs.next()) {
                count = rs.getInt(1);
            }

            // If email exists, delete it
            if (count > 0) {
                String sqlDelete = "DELETE FROM subscribers WHERE email = ?";
                pstmtDelete = conn.prepareStatement(sqlDelete);
                pstmtDelete.setString(1, emailAddress);
                int rowsAffected = pstmtDelete.executeUpdate();

                if (rowsAffected > 0) {
                    System.out.println("You have been successfully unsubscribed.");
                }
            } else {
                System.out.println("Email address not found in our database.");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (pstmtSelect != null) pstmtSelect.close();
                if (pstmtDelete != null) pstmtDelete.close();
                if (conn != null) conn.close();
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        }
    }
}