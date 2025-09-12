import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class EmailUnsubscriber {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String DB_USER = "your_username";
    private static final String DB_PASSWORD = "your_password";

    public static void main(String[] args) {
        String email = "example@example.com"; // Replace with the email to check

        if (emailExists(email)) {
            int result = unsubscribeEmail(email);
            if (result == 1) {
                System.out.println("Email unsubscribed successfully.");
            } else {
                System.out.println("Failed to unsubscribe email.");
            }
        } else {
            System.out.println("Email does not exist in the database.");
        }
    }

    private static boolean emailExists(String email) {
        String query = "SELECT 1 FROM users WHERE email = ?";
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setString(1, email);
            ResultSet resultSet = preparedStatement.executeQuery();
            return resultSet.next();

        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    private static int unsubscribeEmail(String email) {
        // This method should call an external script or service to unsubscribe the email
        // For demonstration, let's assume it returns 1 on success and 0 on failure
        // Replace this with actual script execution logic

        // Simulated script execution
        boolean unsubscribeSuccess = true; // Set based on actual script result
        return unsubscribeSuccess ? 1 : 0;
    }
}