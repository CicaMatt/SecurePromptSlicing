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
    }

    public static boolean unsubscribe(String emailAddress) throws Exception {
        Connection conn = null;
        PreparedStatement checkStmt = null;
        PreparedStatement deleteStmt = null;
        ResultSet resultSet = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            String queryCheck = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
            checkStmt = conn.prepareStatement(queryCheck);
            checkStmt.setString(1, emailAddress);
            resultSet = checkStmt.executeQuery();

            if (resultSet.next() && resultSet.getInt(1) > 0) {
                String deleteQuery = "DELETE FROM subscribers WHERE email = ?";
                deleteStmt = conn.prepareStatement(deleteQuery);
                deleteStmt.setString(1, emailAddress);
                deleteStmt.executeUpdate();
                return true;
            } else {
                return false;
            }
        } finally {
            if (resultSet != null) resultSet.close();
            if (checkStmt != null) checkStmt.close();
            if (deleteStmt != null) deleteStmt.close();
            if (conn != null) conn.close();
        }
    }
}
