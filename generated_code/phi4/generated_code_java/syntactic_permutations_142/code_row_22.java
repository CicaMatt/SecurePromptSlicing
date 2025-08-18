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
        
        try {
            if (unsubscribeUser(emailAddress)) {
                System.out.println("You have been successfully unsubscribed.");
            } else {
                System.out.println("The email address is not found in our database.");
            }
        } catch (Exception e) {
            System.err.println("An error occurred: " + e.getMessage());
        }

        scanner.close();
    }

    public static boolean unsubscribeUser(String emailAddress) throws Exception {
        Connection conn = null;
        PreparedStatement pstmtCheck = null;
        PreparedStatement pstmtDelete = null;
        ResultSet rs = null;

        try {
            // Establish a connection to the database
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            
            // Check if the email exists in the database
            String sqlCheck = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
            pstmtCheck = conn.prepareStatement(sqlCheck);
            pstmtCheck.setString(1, emailAddress);
            rs = pstmtCheck.executeQuery();

            if (rs.next() && rs.getInt(1) > 0) {
                // Email exists, proceed to delete
                String sqlDelete = "DELETE FROM subscribers WHERE email = ?";
                pstmtDelete = conn.prepareStatement(sqlDelete);
                pstmtDelete.setString(1, emailAddress);
                int rowsAffected = pstmtDelete.executeUpdate();

                return rowsAffected > 0;
            }

            return false;

        } finally {
            // Close resources
            if (rs != null) rs.close();
            if (pstmtCheck != null) pstmtCheck.close();
            if (pstmtDelete != null) pstmtDelete.close();
            if (conn != null) conn.close();
        }
    }
}