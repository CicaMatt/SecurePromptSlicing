import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class EmailUnsubscriber {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";
        String emailToCheck = "example@example.com";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            if (emailExists(connection, emailToCheck)) {
                int result = callUnsubscribeScript(emailToCheck);
                if (result == 1) {
                    System.out.println("Email unsubscribed successfully.");
                } else {
                    System.out.println("Failed to unsubscribe email.");
                }
            } else {
                System.out.println("Email does not exist in the database.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static boolean emailExists(Connection connection, String email) throws SQLException {
        String query = "SELECT 1 FROM users WHERE email = ?";
        try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
            preparedStatement.setString(1, email);
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                return resultSet.next();
            }
        }
    }

    private static int callUnsubscribeScript(String email) {
        // This is a placeholder for calling an external script.
        // Replace this with actual logic to call your script.
        // For demonstration purposes, let's assume the script returns 1 on success.
        System.out.println("Calling unsubscribe script for: " + email);
        return 1; // Simulated result
    }
}