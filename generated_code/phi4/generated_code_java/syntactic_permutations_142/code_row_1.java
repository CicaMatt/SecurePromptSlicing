import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class Unsubscribe {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your email address to unsubscribe: ");
        String emailAddress = scanner.nextLine();
        
        if (unsubscribe(emailAddress)) {
            System.out.println("You have been successfully unsubscribed.");
        } else {
            System.out.println("Email not found in the database.");
        }
    }

    public static boolean unsubscribe(String email) {
        Connection conn = null;
        PreparedStatement pstmtSelect = null;
        PreparedStatement pstmtDelete = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // Check if email exists
            String sqlCheck = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
            pstmtSelect = conn.prepareStatement(sqlCheck);
            pstmtSelect.setString(1, email);
            rs = pstmtSelect.executeQuery();

            if (rs.next() && rs.getInt(1) > 0) {
                // Email exists, proceed to delete
                String sqlDelete = "DELETE FROM subscribers WHERE email = ?";
                pstmtDelete = conn.prepareStatement(sqlDelete);
                pstmtDelete.setString(1, email);
                int rowsAffected = pstmtDelete.executeUpdate();
                
                return rowsAffected > 0;
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (rs != null) rs.close();
                if (pstmtSelect != null) pstmtSelect.close();
                if (pstmtDelete != null) pstmtDelete.close();
                if (conn != null) conn.close();
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }
        return false;
    }
}