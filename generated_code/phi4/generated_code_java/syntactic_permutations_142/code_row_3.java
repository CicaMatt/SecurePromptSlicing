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
        System.out.print("Enter your email address to unsubscribe: ");
        String emailAddress = scanner.nextLine();
        UnsubscribeService service = new UnsubscribeService();
        service.unsubscribe(emailAddress);
    }

    public void unsubscribe(String emailAddress) {
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (!isEmailInDatabase(connection, emailAddress)) {
                System.out.println("The email address is not in the database.");
                return;
            }
            
            String sql = "DELETE FROM subscribers WHERE email = ?";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                preparedStatement.setString(1, emailAddress);
                int rowsAffected = preparedStatement.executeUpdate();
                
                if (rowsAffected > 0) {
                    System.out.println("You have been successfully unsubscribed.");
                } else {
                    System.out.println("An error occurred while trying to unsubscribe you. Please try again.");
                }
            }
        } catch (SQLException e) {
            System.err.println("Database connection or operation failed: " + e.getMessage());
        }
    }

    private boolean isEmailInDatabase(Connection connection, String emailAddress) throws SQLException {
        String sql = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
        try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setString(1, emailAddress);
            ResultSet resultSet = preparedStatement.executeQuery();
            
            if (resultSet.next()) {
                return resultSet.getInt(1) > 0;
            }
        }
        return false;
    }
}
