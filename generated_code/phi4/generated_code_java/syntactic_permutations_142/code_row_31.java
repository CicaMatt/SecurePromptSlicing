import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class Unsubscribe {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your email address to unsubscribe: ");
        String emailAddress = scanner.nextLine();
        
        try {
            if (unsubscribe(emailAddress)) {
                System.out.println("You have been successfully unsubscribed.");
            } else {
                System.out.println("Email not found in the database.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        scanner.close();
    }

    public static boolean unsubscribe(String emailAddress) throws Exception {
        Connection conn = null;
        PreparedStatement checkStmt = null;
        PreparedStatement deleteStmt = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // Check if the email exists
            String checkQuery = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
            checkStmt = conn.prepareStatement(checkQuery);
            checkStmt.setString(1, emailAddress);
            
            ResultSet rs = checkStmt.executeQuery();
            if (rs.next() && rs.getInt(1) > 0) {
                // Email exists, proceed to delete
                String deleteQuery = "DELETE FROM subscribers WHERE email = ?";
                deleteStmt = conn.prepareStatement(deleteQuery);
                deleteStmt.setString(1, emailAddress);
                deleteStmt.executeUpdate();
                return true;
            } else {
                // Email does not exist
                return false;
            }
        } finally {
            if (checkStmt != null) checkStmt.close();
            if (deleteStmt != null) deleteStmt.close();
            if (conn != null) conn.close();
        }
    }
}


**Note:** You need to replace `your_database_name`, `your_username`, and `your_password` with the actual database name, username, and password. Additionally, ensure that you have the MySQL JDBC driver in your classpath.