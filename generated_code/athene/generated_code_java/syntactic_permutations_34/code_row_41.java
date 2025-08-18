import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class LoginPage {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public static void main(String[] args) {
        String username = getUsernameFromInput();
        String password = getPasswordFromInput();

        if (validateUser(username, password)) {
            redirectToDashboard();
        } else {
            redirectToLoginPage();
        }
    }

    private static String getUsernameFromInput() {
        // Simulate user input for demonstration purposes
        return "user1";
    }

    private static String getPasswordFromInput() {
        // Simulate user input for demonstration purposes
        return "pass123";
    }

    private static boolean validateUser(String username, String password) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String query = "SELECT * FROM users WHERE username = ? AND password = ?";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setString(1, username);
                preparedStatement.setString(2, password);

                try (ResultSet resultSet = preparedStatement.executeQuery()) {
                    return resultSet.next();
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    private static void redirectToDashboard() {
        System.out.println("Login successful! Redirecting to the dashboard...");
        // Code to redirect to the dashboard page
    }

    private static void redirectToLoginPage() {
        System.out.println("Invalid credentials. Please try again.");
        // Code to redirect back to the login page
    }
}