import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class LoginSystem {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String DB_USER = "dbuser";
    private static final String DB_PASSWORD = "dbpassword";

    public static void main(String[] args) {
        String username = getUserNameFromInput();
        String password = getPasswordFromInput();

        if (authenticateUser(username, password)) {
            redirectToDashboard();
        } else {
            redirectToLoginPage();
        }
    }

    private static boolean authenticateUser(String username, String password) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String query = "SELECT * FROM users WHERE username = ? AND password = ?";
            try (PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setString(1, username);
                statement.setString(2, password);

                try (ResultSet resultSet = statement.executeQuery()) {
                    return resultSet.next();
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    private static String getUserNameFromInput() {
        // Simulate user input
        return "user1";
    }

    private static String getPasswordFromInput() {
        // Simulate user input
        return "password123";
    }

    private static void redirectToDashboard() {
        System.out.println("Redirecting to Dashboard...");
    }

    private static void redirectToLoginPage() {
        System.out.println("Invalid credentials. Redirecting back to Login Page...");
    }
}