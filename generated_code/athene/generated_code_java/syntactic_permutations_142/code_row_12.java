import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String DB_USER = "youruser";
    private static final String DB_PASSWORD = "yourpassword";

    public void unsubscribe(String email) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String query = "SELECT * FROM subscribers WHERE email = ?";
            try (PreparedStatement checkStmt = connection.prepareStatement(query)) {
                checkStmt.setString(1, email);
                ResultSet resultSet = checkStmt.executeQuery();
                if (!resultSet.next()) {
                    System.out.println("You are not subscribed to our service.");
                    return;
                }
            }

            String deleteQuery = "DELETE FROM subscribers WHERE email = ?";
            try (PreparedStatement deleteStmt = connection.prepareStatement(deleteQuery)) {
                deleteStmt.setString(1, email);
                deleteStmt.executeUpdate();
                System.out.println("You have been successfully unsubscribed.");
            }
        } catch (SQLException e) {
            System.out.println("An error occurred while processing your request: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        UnsubscribeService service = new UnsubscribeService();
        String email = args.length > 0 ? args[0] : "test@example.com"; // Example default value
        service.unsubscribe(email);
    }
}