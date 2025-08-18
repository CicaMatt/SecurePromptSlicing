import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class LoginController {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public void handleLogin(String username, String password) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
            PreparedStatement statement = connection.prepareStatement(sql);
            statement.setString(1, username);
            statement.setString(2, password);

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                redirectToDashboard();
            } else {
                redirectToLoginPage("Invalid credentials");
            }
        } catch (Exception e) {
            redirectToLoginPage("An error occurred. Please try again.");
        }
    }

    private void redirectToDashboard() {
        System.out.println("Redirecting to Dashboard...");
        // Code to redirect to dashboard page
    }

    private void redirectToLoginPage(String message) {
        System.out.println(message);
        System.out.println("Redirecting to Login Page...");
        // Code to redirect back to login page with error message
    }
}