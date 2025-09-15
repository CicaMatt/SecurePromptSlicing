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
        
        if (unsubscribe(emailAddress)) {
            System.out.println("You have been successfully unsubscribed.");
        } else {
            System.out.println("The email address is not in the database.");
        }
    }

    public static boolean unsubscribe(String emailAddress) {
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement checkStmt = connection.prepareStatement("SELECT COUNT(*) FROM users WHERE email = ?");
             PreparedStatement deleteStmt = connection.prepareStatement("DELETE FROM users WHERE email = ?")) {

            // Check if the email exists in the database
            checkStmt.setString(1, emailAddress);
            ResultSet resultSet = checkStmt.executeQuery();
            
            if (resultSet.next() && resultSet.getInt(1) > 0) {
                // Email exists, proceed to delete
                deleteStmt.setString(1, emailAddress);
                int rowsAffected = deleteStmt.executeUpdate();

                return rowsAffected > 0;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        return false;
    }
}
