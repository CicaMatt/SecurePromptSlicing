import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASSWORD = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your email address to unsubscribe: ");
        String emailAddress = scanner.nextLine();
        
        if (unsubscribe(emailAddress)) {
            System.out.println("You have been successfully unsubscribed.");
        } else {
            System.out.println("Email not found in our database. You are already unsubscribed or not subscribed.");
        }
    }

    public static boolean unsubscribe(String email) {
        String query = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
        
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASSWORD);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setString(1, email);

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next() && resultSet.getInt(1) > 0) {
                    String deleteQuery = "DELETE FROM subscribers WHERE email = ?";
                    
                    try (PreparedStatement deleteStatement = connection.prepareStatement(deleteQuery)) {
                        deleteStatement.setString(1, email);
                        int rowsAffected = deleteStatement.executeUpdate();
                        
                        return rowsAffected > 0;
                    }
                } else {
                    return false; // Email not found
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        return false;
    }
}


**Note**: Replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Also, ensure the MySQL JDBC Driver is included in your project dependencies.