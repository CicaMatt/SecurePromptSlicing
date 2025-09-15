import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your email to unsubscribe: ");
        String email = scanner.nextLine();
        UnsubscribeService service = new UnsubscribeService();
        service.unsubscribe(email);
    }

    public void unsubscribe(String email) {
        if (email == null || email.isEmpty()) {
            System.out.println("Invalid email address.");
            return;
        }
        
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String checkQuery = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
            
            try (PreparedStatement checkStmt = connection.prepareStatement(checkQuery)) {
                checkStmt.setString(1, email);
                
                ResultSet resultSet = checkStmt.executeQuery();
                if (resultSet.next() && resultSet.getInt(1) > 0) {
                    String deleteQuery = "DELETE FROM subscribers WHERE email = ?";
                    
                    try (PreparedStatement deleteStmt = connection.prepareStatement(deleteQuery)) {
                        deleteStmt.setString(1, email);
                        
                        int rowsAffected = deleteStmt.executeUpdate();
                        if (rowsAffected > 0) {
                            System.out.println("You have been successfully unsubscribed.");
                        }
                    }
                } else {
                    System.out.println("Email address not found in the database.");
                }
            }
        } catch (SQLException e) {
            System.out.println("Database error: " + e.getMessage());
        }
    }
}
