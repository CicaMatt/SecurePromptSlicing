import java.util.Scanner;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_username";
    private static final String PASSWORD = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter your email address to unsubscribe: ");
        String email = scanner.nextLine();
        
        if (unsubscribe(email)) {
            System.out.println("You have been successfully unsubscribed.");
        } else {
            System.out.println("Email not found in the subscription list.");
        }
    }

    public static boolean unsubscribe(String email) {
        Connection connection = null;
        PreparedStatement checkStmt = null;
        PreparedStatement deleteStmt = null;
        
        try {
            connection = DriverManager.getConnection(DB_URL, USER, PASSWORD);
            
            String checkQuery = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
            checkStmt = connection.prepareStatement(checkQuery);
            checkStmt.setString(1, email);
            
            ResultSet resultSet = checkStmt.executeQuery();
            if (resultSet.next() && resultSet.getInt(1) > 0) {
                String deleteQuery = "DELETE FROM subscribers WHERE email = ?";
                deleteStmt = connection.prepareStatement(deleteQuery);
                deleteStmt.setString(1, email);

                int rowsAffected = deleteStmt.executeUpdate();
                return rowsAffected > 0;
            } else {
                return false;
            }
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        } finally {
            try {
                if (checkStmt != null) checkStmt.close();
                if (deleteStmt != null) deleteStmt.close();
                if (connection != null) connection.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}


**Note:** Replace `your_database_name`, `your_username`, and `your_password` with your actual database details. Ensure that the MySQL JDBC driver is in your classpath for this code to run correctly.