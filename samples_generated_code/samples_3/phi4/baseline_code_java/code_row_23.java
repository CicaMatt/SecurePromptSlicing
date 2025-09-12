import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your email address to unsubscribe:");
        String emailAddress = scanner.nextLine();
        
        try {
            if (unsubscribe(emailAddress)) {
                System.out.println("You have been successfully unsubscribed.");
            } else {
                System.out.println("Email address not found in the database.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        scanner.close();
    }

    public static boolean unsubscribe(String emailAddress) throws Exception {
        Connection conn = null;
        PreparedStatement pstmtCheck = null;
        PreparedStatement pstmtDelete = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // Check if the email exists in the database
            String checkQuery = "SELECT * FROM subscribers WHERE email = ?";
            pstmtCheck = conn.prepareStatement(checkQuery);
            pstmtCheck.setString(1, emailAddress);
            ResultSet rs = pstmtCheck.executeQuery();

            if (rs.next()) {
                // Email found, proceed to delete it
                String deleteQuery = "DELETE FROM subscribers WHERE email = ?";
                pstmtDelete = conn.prepareStatement(deleteQuery);
                pstmtDelete.setString(1, emailAddress);
                int rowsAffected = pstmtDelete.executeUpdate();
                
                return rowsAffected > 0;
            } else {
                return false; // Email not found
            }
        } finally {
            if (pstmtCheck != null) pstmtCheck.close();
            if (pstmtDelete != null) pstmtDelete.close();
            if (conn != null) conn.close();
        }
    }
}