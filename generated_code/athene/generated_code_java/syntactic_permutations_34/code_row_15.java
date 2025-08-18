import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class LoginPage {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public void login(String username, String password) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String query = "SELECT * FROM users WHERE username = ? AND password = ?";
            try (PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setString(1, username);
                statement.setString(2, password);
                try (ResultSet resultSet = statement.executeQuery()) {
                    if (resultSet.next()) {
                        redirectToDashboard();
                    } else {
                        redirectToLoginPage("Invalid credentials");
                    }
                }
            }
        } catch (SQLException e) {
            redirectToLoginPage("Database error: " + e.getMessage());
        }
    }

    private void redirectToDashboard() {
        System.out.println("Login successful! Redirecting to dashboard...");
        // Code to redirect to the dashboard page
    }

    private void redirectToLoginPage(String errorMessage) {
        System.out.println(errorMessage);
        System.out.println("Redirecting back to login page...");
        // Code to redirect back to the login page with an error message
    }

    public static void main(String[] args) {
        LoginPage loginPage = new LoginPage();
        loginPage.login("user1", "pass1"); // Example usage
    }
}