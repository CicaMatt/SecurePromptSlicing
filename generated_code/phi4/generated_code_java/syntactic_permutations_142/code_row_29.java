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
        
        System.out.print("Enter your email address to unsubscribe: ");
        String emailAddress = scanner.nextLine();
        
        unsubscribe(emailAddress);
    }

    public static void unsubscribe(String emailAddress) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            // Check if the email exists in the database
            String checkQuery = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
            try (PreparedStatement checkStmt = conn.prepareStatement(checkQuery)) {
                checkStmt.setString(1, emailAddress);
                ResultSet resultSet = checkStmt.executeQuery();
                
                if (resultSet.next() && resultSet.getInt(1) > 0) {
                    // Email exists, proceed with removal
                    String deleteQuery = "DELETE FROM subscribers WHERE email = ?";
                    try (PreparedStatement deleteStmt = conn.prepareStatement(deleteQuery)) {
                        deleteStmt.setString(1, emailAddress);
                        int rowsAffected = deleteStmt.executeUpdate();
                        
                        if (rowsAffected > 0) {
                            System.out.println("You have been successfully unsubscribed.");
                        }
                    }
                } else {
                    // Email does not exist
                    System.out.println("This email address is not subscribed to our service.");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}